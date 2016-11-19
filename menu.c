#include "menu.h"

HANDLE hout;

void intiApplication()
{
	//�����ӭ����
	system("cls");
	printf("\n\t\t\t ����������������������\n");
	printf("\t\t\t ����ӭʹ����������Ϸ��\n");
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

void GetInput(int *nSelect)
{
	int ch=_getch();

	COORD coord;			//��Ļ�ϵ�����
	coord.X = 1;
	coord.Y = 1;

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	while (1)
	{
		while (ch == 0xE0 || ch == 0x0d) {

			printf("\b\b  ");
			

			GetConsoleScreenBufferInfo(hout, &csbi);
			coord.X = csbi.dwCursorPosition.X;// �õ�����x��ֵ
			coord.Y = csbi.dwCursorPosition.Y;// �õ�����y��ֵ

			coord.X += 12;
			SetConsoleCursorPosition(hout, coord);
			printf("\b\b  ");
			coord.X -= 12;
			SetConsoleCursorPosition(hout, coord);

			if (ch == 0x0d)				      // ����ǻس�
				return *nSelect;
			ch = _getch();

			//��
			if (ch == 0x48)
			{
				if ((*nSelect) == 1)
				{
					(*nSelect) = OPTIONS;
					coord.Y += OPTIONS-1;

				}
				else
				{
					(*nSelect)--;
					coord.Y--;

				}
			}
			//��
			else if (ch == 0x50)
			{
				if ((*nSelect) == OPTIONS)
				{
					coord.Y -= OPTIONS-1;
					(*nSelect) = 1;
				}
				else
				{
					coord.Y++;
					(*nSelect)++;
				}
			}

			SetConsoleCursorPosition(hout, coord);
			printf("\b\b��");
			coord.X += 12;
			SetConsoleCursorPosition(hout, coord);
			printf("\b\b��");
			coord.X -= 12;
			SetConsoleCursorPosition(hout, coord);


			ch = _getch();

		}
		ch = _getch();
	}
}

int printMainMenu()
{
	int nSelect = 1; // Ĭ��Ϊ1

	printf("\n");
	printf("\t\t========================================\n\n");
	printf("\t\t\t        NEW GAME\n");
	printf("\t\t\t        �������\n");
	printf("\t\t\t        ��������\n");
	printf("\t\t\t        �鿴����\n");
	printf("\t\t\t        ��������\n");
	printf("\t\t\t        �˳���Ϸ\n");
	printf("\n\t\t----------------------------------------\n");
	printf("\t\t��ʹ�á�����ѡ���ܣ����س���ȷ�ϣ�");
	
	gotoxy(42, 8);
	printf("��");
	gotoxy(30,8);
	printf("��");
	hout = GetStdHandle(STD_OUTPUT_HANDLE);					 //��ñ�׼����豸���  
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
	GetInput(&nSelect); 
	nSelect = nSelect % OPTIONS;
	
	/*
	// ����û�������
	scanf_s("%d", &nSelect);
	
	// �������������
	char s[1024];
	fgets(s, 1024, stdin);
	// fflush(stdin);
	*/

	
	// �����û�ѡ��Ĳ˵������
	return nSelect;

}

void PlayGame()
{
	Point spPoint;						// �����
	int nStep = 0;						// ���ӵĲ���
	int nResult = JUDGE_CONTINUE;		// ����жϽ��

	// ��ʼ����Ϸ����
	InitStatus();

	// ��������
	PrintChess();
	//PrintBound();

	// �����ʼ��ʾ
	PrintPrompt();

	// ��������
	PrintChess();
	//PrintBound();

	//��ʼ���壬ʹ��do��while��������һ�ӣ��ٽ��м���Ƿ��ʤ
	do {

		spPoint.status = nStep % 2;
		// ����û���������
		InputPoint(&spPoint);

		// ���������״̬
		SetStatus(spPoint);

		// ��������
		PrintChess();

		//��������
		nStep++;

		// �ж����
		nResult = JudgeGame(spPoint);
	} while (nResult == JUDGE_CONTINUE);	// ѭ�����ӣ�����ʤʱ�������ѭ��
	
	// ��Ϸ�����ж������Ӯ��ƽ��
	if (nResult == JUDGE_WIN)
	{
		PrintWinner(spPoint);	// ���ʤ����Ϣ
	}
	else if (nResult == JUDGE_DRAW)		// ���������Ϣ
	{
		PrintDraw();
	}
}

void PrintGameRule()
{
	system("cls");
	printf("��������������������������������������������\n");
	printf("��Ϸ����\n");
	printf("��������������������������������������������\n");
	printf("1��������Ϊ������֮��ľ�����\n");
	printf("2���������У�������С�\n");
	printf("3������Ϊ��15*15��\n");
	printf("4��ͬɫ�����ں���бĳһ��������5��Ϊʤ��\n");
	printf("5���Ծ�˫����δ�γ���������������Ϊ���塣\n");
	printf("6�����̺�������ĸ��ţ����������ֱ�š�\n");
	printf("7���û�ѡ��ʼ��Ϸ���ɿ�ʼ���壡\n");
	printf("8���û������Ӧ����к����кţ���:A0��\n");
	printf("��������������������������������������������\n");
	printf("����������ء�\n");
	_getch();
}

void PrintAboutUs()
{
	system("cls");
	printf("��������������������������������������������\n");
	printf("��������\n");
	printf("��������������������������������������������\n");
	printf("\t��������Ϸ Verison 1.0 Beta\n");
	printf("��Ȩ���� 2016 ���� www.ghostcoming.space\n");
	printf("��������������������������������������������\n");
	printf("����������ء�\n");
	_getch();
}
