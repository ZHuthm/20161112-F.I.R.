#ifndef _RANK_SERVICE_H_
#define _RANK_SERVICE_H_

#include "rank_file.h"

///////////////////////////////////////////////////////
// 函数声明

/****************************************************
[函数名称] JudgeOrder
[函数功能] 判断排名先后
[函数参数] const int: nStep游戏步数
[返 回 值] int: 排名位次
****************************************************/
int JudgeOrder(const int);

/****************************************************
[函数名称] InsertRank
[函数功能] 插入排名信息
[函数参数] const int: nPostion 插入点,const Rank
[返 回 值] void
****************************************************/
void InsertRank(const int, const Rank);

/****************************************************
[函数名称] SaveRanks
[函数功能] 将排名信息保存到文件中
[函数参数] 无
[返 回 值] 无
****************************************************/
void SaveRanks();

/****************************************************
[函数名称] GetRankSize
[函数功能] 获得当前排行榜中的条目数
[函数参数] 无
[返 回 值] int: 当前排行榜中的条目数
****************************************************/
int GetRankSize();

int GetRanks(Rank *, const int);

/****************************************************
[函数名称] InitRanks
[函数功能] 初始化玩家数组
[函数参数] 无
[返 回 值] 无
****************************************************/
void InitRanks();

///////////////////////////////////////////////////////

#endif