// Copyright 2020-2020 The TZIOT Authors. All rights reserved.
// ͳ��ģ��
// Authors: jdh99 <jdh821@163.com>

#include "statistics.h"
#include "tzmalloc.h"
#include "lagan.h"
#include "tztype.h"

#include <stdio.h>
#include <string.h>

#define TAG "statistics"

#define MALLOC_TOTAL 4096

static int gMid = -1;
static int gMaxItemNum = 0;
static StatisticsItem* gItems = NULL;
static int gItemsNum = 0;

// StatisticsLoad ģ������
// maxItemNum ���ͳ��������
bool StatisticsLoad(int maxItemNum) {
    // ����Ҫ�ظ�����.����ظ��������û������ȷ���ʧ��
    if (gMaxItemNum == maxItemNum) {
        LI(TAG, "load success.repeat load");
        return true;
    }
    if (gItemsNum != 0) {
        LE(TAG, "load failed!repeat load and max item num is not same");
        return false;
    }

    gMid = TZMallocRegister(0, TAG, MALLOC_TOTAL);
    if (gMid < 0) {
        LE(TAG, "load failed!malloc register failed");
        return false;
    }

    gItems = TZMalloc(gMid, maxItemNum * (int)sizeof(StatisticsItem));
    if (gItems == NULL) {
        LE(TAG, "load failed!malloc items failed");
        return false;
    }

    LI(TAG, "load success");
    gMaxItemNum = maxItemNum;
    return true;
}

// StatisticsRegister ע��һ��ͳ����
// ע��ɹ����ؿ���ʹ�õ�ͳ����id,ʧ�ܷ���-1
int StatisticsRegister(const char* name) {
    if (gItemsNum >= gMaxItemNum) {
        LE(TAG, "%s register failed.items is too many", name);
        return -1;
    }

    int nameLen = (int)strlen(name);
    if (nameLen == 0) {
        LE(TAG, "%s register failed.name len is 0", name);
        return -1;
    }
    if (nameLen > STATISTICS_NAME_LEN_MAX) {
        LW(TAG, "%s is too long,truncate name", name);
        nameLen = STATISTICS_NAME_LEN_MAX;
    }

    LI(TAG, "%s register success", name);
    memset(&gItems[gItemsNum], 0, sizeof(TZMallocUser));
    memcpy(gItems[gItemsNum].Name, name, (size_t)nameLen);
    gItems[gItemsNum].Value = 0;
    gItemsNum++;
    return gItemsNum - 1;
}

// StatisticsAdd ͳ����ֵ����
void StatisticsAdd(int itemId) {
    if (itemId < 0 || itemId >= gItemsNum) {
        LE(TAG, "add failed!item id is wrong", itemId);
        return;
    }
    gItems[itemId].Value++;
}

// StatisticsClear ���ͳ����
void StatisticsClear(int itemId) {
    if (itemId < 0 || itemId >= gItemsNum) {
        LE(TAG, "clear failed!item id is wrong", itemId);
        return;
    }
    gItems[itemId].Value = 0;
}

// StatisticsAdd ����ͳ����ֵ
void StatisticsSet(int itemId, int value) {
    if (itemId < 0 || itemId >= gItemsNum) {
        LE(TAG, "set failed!item id is wrong", itemId);
        return;
    }
    gItems[itemId].Value = value;
}

// StatisticsClear �������ͳ����
void StatisticsClearAll(void) {
    for (int i = 0; i < gItemsNum; i++) {
        gItems[i].Value = 0;
    }
}

// StatisticsGetItem ��ȡĳ��ͳ��
// ���ص������NULL,�����ȡʧ��
StatisticsItem* StatisticsGetItem(int itemId) {
    if (itemId < 0 || itemId >= gItemsNum) {
        LE(TAG, "get failed!item id is wrong", itemId);
        return NULL;
    }
    return &gItems[itemId];
}

// StatisticsGetItemNum ��ȡͳ������
int StatisticsGetItemNum(void) {
    return gItemsNum;
}

// StatisticsOutput ���ͳ����Ϣ
void StatisticsOutput(char* out, int outSize) {
    if (out == NULL || outSize <= 0 || gItemsNum == 0) {
        LE(TAG, "output failed.param is wrong");
        return;
    }
    
    out[0] = '\0';
    char str[TZ_BUFFER_LEN];
    int usedSize = 0;
    for (int i = 0; i < gItemsNum; i++) {
        sprintf(str, "%s:%d\n", gItems[i].Name, gItems[i].Value);
        usedSize += (int)strlen(str);
        if (usedSize >= outSize) {
            return;
        }
        strcat(out, str);
    }
}

// StatisticsPrint ��ӡͳ����Ϣ
void StatisticsPrint(void) {
    for (int i = 0; i < gItemsNum; i++) {
        LI(TAG, "%s:%d", gItems[i].Name, gItems[i].Value);
    }
}
