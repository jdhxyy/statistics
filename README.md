# statistics

## 1. 介绍
统计模块。

## 2. API
```c
// StatisticsLoad 模块载入
// maxItemNum 最大统计项数量
bool StatisticsLoad(int maxItemNum);

// StatisticsRegister 注册一个统计项
// 注册成功返回可以使用的统计项id,失败返回-1
int StatisticsRegister(const char* name);

// StatisticsAdd 统计项值自增
void StatisticsAdd(int itemId);

// StatisticsClear 清除统计项
void StatisticsClear(int itemId);

// StatisticsAdd 设置统计项值
void StatisticsSet(int itemId, int value);

// StatisticsClear 清除所有统计项
void StatisticsClearAll(void);

// StatisticsGetItem 读取某项统计
// 返回的如果是NULL,代表读取失败
StatisticsItem* StatisticsGetItem(int itemId);

// StatisticsGetItemNum 读取统计项数
int StatisticsGetItemNum(void);

// StatisticsOutput 输出统计信息
void StatisticsOutput(char* out, int outSize);

// StatisticsPrint 打印统计信息
void StatisticsPrint(void);
```
