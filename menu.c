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
	// ����������Ϣ
	SaveRanks();

	// �ͷ�����ռ�
	ClearRanks();

	// �����Ϸ������ʾ��Ϣ
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
				return;
			ch = _getch();

			//��
			if (ch == 0x48)
			{
				if ((*nSelect) == 1)
				{
					(*nSelect) = OPTIONS;
					coord.Y += 2 * (OPTIONS - 1);
				}
				else
				{
					(*nSelect)--;
					coord.Y-=2;
				}
			}
			//��
			else if (ch == 0x50)
			{
				if ((*nSelect) == OPTIONS)
				{
					coord.Y -= 2 * (OPTIONS - 1);
					(*nSelect) = 1;
				}
				else
				{
					coord.Y+=2;
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

	printf("\n\t\t========================================\n\n");
	printf("\t\t\t        ���˶�ս\n\n");
	printf("\t\t\t        �˻���ս\n\n");
	printf("\t\t\t        �������\n\n");
	printf("\t\t\t        ��������\n\n");
	printf("\t\t\t        �鿴����\n\n");
	printf("\t\t\t        ��������\n\n");
	printf("\t\t\t        �˳���Ϸ\n");
	printf("\n\t\t----------------------------------------\n");
	printf("\t\t��ʹ�á�����ѡ���ܣ����س���ȷ�ϣ�");
	
	gotoxy(42, 8);
	printf("��");
	gotoxy(30,8);
	printf("��");
	hout = GetStdHandle(STD_OUTPUT_HANDLE);					 // ��ñ�׼����豸���  

	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };				 // ���ع��
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

void PlayGame(int nSelect)
{
	Point spPoint;						// �����
	int nStep = 0;						// ���ӵĲ���
	int nResult = JUDGE_CONTINUE;		// ����жϽ��

	if (nSelect == 1)					
	{
		// ��ʼ����Ϸ
		// ��ʼ����Ϸ����
		InitStatus();
	}
	else if (nSelect == 3)				
	{
		// ������Ϸ
		LoadGame(&nStep);
	}

	// ��������
	PrintChess();
	//PrintBound();

	// �����ʼ��ʾ
	PrintStartPrompt();

	// ��������
	PrintChess();
	//PrintBound();

	//��ʼ���壬ʹ��do��while��������һ�ӣ��ٽ��м���Ƿ��ʤ
	do 
	{

		spPoint.status = nStep % 2;

		// ʹ�÷��������û���������
		
		switch (InputCoord(&spPoint))
		{
		case 1:			// �����ȷ����
			break;
		case 0:			// ���ѡ���˳���Ϸ
			if (PrintPrompt() == 0)
			{
				// ����Ƿ񱣴���Ϸ
				SaveGame(nStep);
			}				
			return;
			break;
		case -1:		// ����˳�ѡ���
			PrintChess();
			continue;
		}

		// ͨ��������������
		// InputPoint(&spPoint);

		// ���������״̬
		SetStatus(spPoint);

		// ��������
		PrintChess();

		//��������
		nStep++;

		// �ж����
		nResult = JudgeGame(spPoint);
		
		// ѭ�����ӣ�����ʤʱ�������ѭ��
	} while (nResult == JUDGE_CONTINUE);	
	
	// ��Ϸ�����ж������Ӯ��ƽ��
	if (nResult == JUDGE_WIN)
	{
		// ���ʤ����Ϣ
		PrintWinner(spPoint);	
		// ����������Ϣ
		PrintAddRank(nStep);
	}
	else if (nResult == JUDGE_DRAW)		
	{
		// ���������Ϣ
		PrintDraw();			
	}

	// ����������Ϣ
	SaveRanks();
}

void PrintGameRule()
{
	// �����Ϸ�������
	system("cls");
	gotoxy(1, 6);
	printf("\t\t��������������������������������������������\n");
	printf("\t\t��Ϸ����\n");
	printf("\t\t��������������������������������������������\n");
	printf("\t\t1��������Ϊ������֮��ľ�����\n");
	printf("\t\t2���������У�������С�\n");
	printf("\t\t3������Ϊ��15*15��\n");
	printf("\t\t4��ͬɫ�����ں���бĳһ��������5��Ϊʤ��\n");
	printf("\t\t5���Ծ�˫����δ�γ���������������Ϊ���塣\n");
	printf("\t\t6�����̺�������ĸ��ţ����������ֱ�š�\n");
	printf("\t\t7���û�ѡ��ʼ��Ϸ���ɿ�ʼ���壡\n");
	printf("\t\t8���û������Ӧ����к����кţ���:A0��\n");
	printf("\t\t��������������������������������������������\n");
	printf("\t\t����������ء�\n");
	_getch();
}

void PrintAboutUs()
{
	// ����������ǽ���
	system("cls");
	gotoxy(1, 6);
	printf("\t\t��������������������������������������������\n");
	printf("\t\t��������\n");
	printf("\t\t��������������������������������������������\n");
	printf("\t\t\t��������Ϸ Verison 1.0 Beta\n");
	printf("\t\t��Ȩ���� 2016 ���� www.ghostcoming.space\n");
	printf("\t\t��������������������������������������������\n");
	printf("\t\t����������ء�\n");
	_getch();
}

void PrintAddRank(const int nStep)
{
	char acName[64];				// ����û����������
	Rank srRank;					// ������Ϣ�ṹ�����

	int nOrder = JudgeOrder(nStep);	// �ж�����

	// �ж������Ƿ���ǰ10֮��
	if (nOrder <= 10)
	{
		// ��ʾ�û���������
		gotoxy(24, 24);
		printf("��ϲ������ʤ������������%d����\n",nStep);
		printf("\t\t---------------------------------------------\n");
		printf("\t\t������������");
		scanf_s("%s", acName, 64);
		strcpy_s(srRank.name, sizeof(srRank.name), acName);
		srRank.step = nStep;
	}
	else
	{
		gotoxy(24, 24);
		system("pause");
	}
	// ���������Ϣ
	InsertRank(nOrder - 1, srRank);
	
}

void PrintRanklist()
{
	system("cls");
	const int nMaxSize = GetRankSize();			// ��ø���
	int nSize = 0;								// ʵ�ʵ���Ҹ�������������£���ֵ��nMaxSize��ȣ�
	Rank* psrRanks = NULL;						// �����������
	int nIndex = 0;								// ��������������

	// ������а����ͷ
	gotoxy(1, 6);
	printf("\t\t��������������������������������������������\n");
	printf("\t\t���а�\n");
	printf("\t\t��������������������������������������������\n");
	printf("\t\t����\t\t�û���\t\t����\n");

	// ����nMaxSize��Rank�ռ䣬������һ��Rank����ռ�
	psrRanks = (Rank*)malloc(sizeof(Rank)*nMaxSize);
	// ��ʼ���µĿռ䣬ȫ����ֵΪ0
	memset(psrRanks, 0, sizeof(Rank)*nMaxSize);
	
	// �������б�
	nSize = GetRanks(psrRanks, nMaxSize);

	// �����������
	for (nIndex = 0; nIndex < nMaxSize; nIndex++)
	{
		printf("\t\t%d\t\t%s\t\t%d\n", nIndex + 1, psrRanks[nIndex].name, psrRanks[nIndex].step);
	}

	// �ͷſ��ٵĿռ�
	free(psrRanks);

	// ��ʾ�û����ز���
	printf("\t\t��������������������������������������������\n");
	printf("\t\t����������ء�\n");
	_getch();
}
