#include <stdio.h> //printf()����ͷ�ļ�
// stdio "standard buffered input & output
// ���������ı�׼����������õ���׼�����������ʱ����Ҫ�������ͷ�ļ���
#include <Windows.h>
#include <conio.h>
#include "menu.h"
#include "game_service.h"

#define MAX 15

void intiApplication()
{
	//�����ӭ����
	system("cls");
	printf("\n\t\t\t ����������������������\n");
	printf("\t\t\t ����ӭ������������Ϸ��\n");
	printf("\t\t\t ����������������������\n");
}

void exitApplication()
{
	// �˳�
	for (int i = 5; i != 0; i--)
	{
		system("cls");
		printf("\n\t\t\t����������������������\n");
		printf("\t\t\t��     ��лʹ��!    ��\n");
		printf("\t\t\t��    (%d����˳�)   ��\n", i);
		printf("\t\t\t����������������������\n");
		Sleep(1000);
	}
}

/****************************************************
[��������] main
[��������] ����������������ں���
[��������] ��
[�� �� ֵ] int: ˵��������˳�״̬
****************************************************/
int main(void)
{
	int nSelect;
	do
	{
		//�����ӭ����
		intiApplication();

		nSelect = printMainMenu();
		switch (nSelect)
		{
		case 0:// �˳�
			continue;

		case 1:// ��ʼ��Ϸ
			system("cls");
			PlayGame();
			break;

		case 2:// ������� 
			printf("\t\t�������");
			break;

		case 3:// ���а�
			printf("\t\t���а�");
			break;

		case 4:// �鿴����
			printf("\t\t�鿴����");
			break;

		case 5:// ��������
			printf("\t\t��������");
			break;

		default:
			printf("\t\t����������ȷ��ѡ�");

		}
		gotoxy(17,12);
		system("pause");
	} while (nSelect != 0);

	exitApplication();
	return 0;// �������0���������������˳���
}

