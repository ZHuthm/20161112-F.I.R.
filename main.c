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
	// ���ѡ��
	int nSelect;
	
	// �����������
	InitRanks();
	
	do
	{
		//�����ӭ����
		intiApplication();
		
		// ͨ�������ѡ����
		nSelect = printMainMenu();

		switch (nSelect)
		{
			
		case 0:// �˳�
			continue;

		case 1:// ����ģʽ
			//����Ϊѡ����Ϸģʽ�����ػ����½�
			PlayGame(nSelect);			
			break;

		case 2:// ����ģʽ
			gotoxy(33, 25);
			printf("�˻���ս\n");
			gotoxy(24, 27);
			system("pause");
			break;

		case 3:// ������� 
			PlayGame(nSelect);
			break;

		case 4:// ���а�
			PrintRanklist();
			break;

		case 5:// �鿴����
			PrintGameRule();
			break;

		case 6:// ��������
			PrintAboutUs();
			break;

		default:
			printf("��bug����");
		}

	} while (nSelect != 0);

	// �˳����򣬲���������������˳�����
	exitApplication();
	
	// �������0���������������˳���
	return 0;
}

