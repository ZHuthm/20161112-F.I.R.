#include <stdio.h> //printf()����ͷ�ļ�
// stdio "standard buffered input & output
// ���������ı�׼����������õ���׼�����������ʱ����Ҫ�������ͷ�ļ���
#include <Windows.h>
#include <conio.h>
#include "menu.h"


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

		case 1:// ����ģʽ
			system("cls");
			PlayGame();
			break;

		case 2:// ����ģʽ
			gotoxy(33, 25);
			printf("�˻���ս\n");
			gotoxy(24, 27);
			system("pause");
			break;

		case 3:// ������� 
			gotoxy(33, 25);
			printf("�������\n");
			gotoxy(24, 27);
			system("pause");
			break;

		case 4:// ���а�
			gotoxy(33, 25);
			printf("��������\n");
			gotoxy(24, 27);
			system("pause");
			break;

		case 5:// �鿴����
			PrintGameRule();
			break;

		case 6:// ��������
			PrintAboutUs();
			break;

		default:
			printf("\t\t����������ȷ��ѡ�");
		}

	} while (nSelect != 0);

	exitApplication();
	return 0;// �������0���������������˳���
}

