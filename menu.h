#pragma once
#include <stdio.h> 
#include <windows.h>
#include <conio.h>
#include <stdlib.h> 
#include "game_service.h"

#define OPTIONS 6


///////////////////////////////////////////////////////
// ��������

// ��ʼ��Ӧ�ó���
void intiApplication();

// ����Ӧ�ó���
void exitApplication();

// ͨ�����¼����ѡ��
void GetInput(int *nSelect);

/****************************************************
[��������] printMainMenu
[��������] ����˵�������ȡ�û�ѡ��
[��������] ��
[�� �� ֵ] char: �����û�ѡ��
****************************************************/
int printMainMenu();

/****************************************************
[��������] PlayGame
[��������] ��ʼ��Ϸ
[��������] ��
[�� �� ֵ] ��
****************************************************/
void PlayGame();

void PrintGameRule();

void PrintAboutUs();

///////////////////////////////////////////////////////