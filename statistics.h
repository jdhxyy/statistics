// Copyright 2020-2021 The jdh99 Authors. All rights reserved.
// ͳ��ģ��
// Authors: jdh99 <jdh821@163.com>

#ifndef STATISTICS_H
#define STATISTICS_H

#include <stdint.h>
#include <stdbool.h>

// ͳ����������ֽ���
#define STATISTICS_NAME_LEN_MAX 32

#pragma pack(1)

// ͳ����
typedef struct {
    char Name[STATISTICS_NAME_LEN_MAX + 1];
    int Value;
} StatisticsItem;

#pragma pack()

// StatisticsLoad ģ������
// maxItemNum ���ͳ��������
bool StatisticsLoad(int maxItemNum);

// StatisticsRegister ע��һ��ͳ����
// ע��ɹ����ؿ���ʹ�õ�ͳ����id,ʧ�ܷ���-1
int StatisticsRegister(const char* name);

// StatisticsAdd ͳ����ֵ����
void StatisticsAdd(int itemId);

// StatisticsClear ���ͳ����
void StatisticsClear(int itemId);

// StatisticsAdd ����ͳ����ֵ
void StatisticsSet(int itemId, int value);

// StatisticsClear �������ͳ����
void StatisticsClearAll(void);

// StatisticsGetItem ��ȡĳ��ͳ��
// ���ص������NULL,�����ȡʧ��
StatisticsItem* StatisticsGetItem(int itemId);

// StatisticsGetItemNum ��ȡͳ������
int StatisticsGetItemNum(void);

// StatisticsOutput ���ͳ����Ϣ
void StatisticsOutput(char* out, int outSize);

// StatisticsPrint ��ӡͳ����Ϣ
void StatisticsPrint(void);

#endif
