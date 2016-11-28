#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <windows.h>
#include <conio.h>
#include <stdlib.h> 

#include "game_service.h"
#include "rank_service.h"

#define OPTIONS 7						// 主菜单选项数量


///////////////////////////////////////////////////////
// 函数声明

// 初始化应用程序
void intiApplication();

// 结束应用程序
void exitApplication();

// 通过上下键获得选项
void GetInput(int *nSelect);

/****************************************************
[函数名称] printMainMenu
[函数功能] 输出菜单，并获取用户选择
[函数参数] 无
[返 回 值] char: 返回用户选项
****************************************************/
int printMainMenu();

/****************************************************
[函数名称] PlayGame
[函数功能] 开始游戏
[函数参数] int : 游戏模式
[返 回 值] 无
****************************************************/
void PlayGame(int);

/****************************************************
[函数名称] PrintGameRule
[函数功能] 输出游戏规则
[函数参数] 无
[返 回 值] 无
****************************************************/
void PrintGameRule();

/****************************************************
[函数名称] PrintAboutUs
[函数功能] 输出关于我们
[函数参数] 无
[返 回 值] 无
****************************************************/
void PrintAboutUs();

/****************************************************
[函数名称] PrintAddRank
[函数功能] 输出添加玩家排名信息
[函数参数] 无
[返 回 值] 无
****************************************************/
void PrintAddRank(const int);

/****************************************************
[函数名称] PrintRanklist
[函数功能] 输出排名列表
[函数参数] 无
[返 回 值] 无
****************************************************/
void PrintRanklist();

///////////////////////////////////////////////////////