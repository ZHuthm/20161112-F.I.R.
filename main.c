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
			PrintGameRule();
			break;

		case 5:// ��������
			PrintAboutUs();
			break;

		default:
			printf("\t\t����������ȷ��ѡ�");
		}

	} while (nSelect != 0);

	exitApplication();
	return 0;// �������0���������������˳���
}

