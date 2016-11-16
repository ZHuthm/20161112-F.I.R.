#include "game_service.h"
#include "global.h"
#include <windows.h>

int AnChessStatus[15][15];

void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void InitStatus()
{
	//�к����к�����ֵ
	int i, j;

	// ��ʼ��״ֵ̬��ʹ��˫ѭ��������ά����
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
			AnChessStatus[i][j] = STATUS_BLANK;
}

int GetStatus(const int nRow, const int nCol)
{
	return AnChessStatus[nRow][nCol];
}

void SetStatus(const int nRow, const int nCol,int nStatus)
{
	AnChessStatus[nRow][nCol] = nStatus;
}

void InputPoint(int * pnRow, int * pnCol, const int nColor)
{
	char acPoint[8];					// ��������û�����
	int nStatus = STATUS_BLANK;			// ����״̬����ʼ��Ϊ��
	int legal = 1;
	
	do
	{
		//�Դ˱�ʶ����ʾ�û�������
		printf("\n\t\t==========================================\n");
		//����ִ�ӷ�����ʾ�û���������
		if (nColor == 0)					// �ڷ�ִ��
		{
			printf("\t\t�����£������������ţ��磺A1����");
		}
		else if (nColor == 1)				// �׷�ִ��
		{
			printf("\t\t�����£������������ţ��磺A1����");
		}

		// ����û����������
		//getchar();
		fgets(acPoint, 8, stdin);
		fflush(stdin);

		*pnCol = toupper(acPoint[0]) - 'A';	// ���ַ�ת��Ϊ��дӢ����ĸ,��Ӧ��ά����ĵ�һ���±�Ϊ0
		*pnRow = atoi(&acPoint[1]) - 1;		// �ַ����ĵڶ�����ĸ��Ϊ���֣�ʹ��atoi��������ת��

		// �ж�������кź��к��Ƿ���Ч
		if (*pnRow < 0 || *pnRow>14 || *pnCol < 0 || *pnCol >14)
		{
			legal = 0;						// �Ƿ�����
			printf("\t\t���겻���ڣ���ȷ�����룡\n");
			continue;
		}

		// ���������״ֵ̬
		nStatus = GetStatus(*pnRow, *pnCol);

		//�ж�״̬
		if (nStatus != STATUS_BLANK)		// ��״̬��Ϊ���ǣ���������
		{
			legal = 0;						// �Ƿ�����
			// ��ǰλ���Ѿ��������ӣ���ʾ�û�
			printf("\t\t�������ӣ�%d%dλ�ò�������\n", *pnCol, *pnRow);
			continue;
		}

		// ����������Ч���Ҹ�����״̬ΪBLANK����Ϊ�Ϸ�λ��
		legal = 1;							// �������Ϸ�

	} while (legal==0);						// ����Ƿ�����Ҫ��������

}

void PrintPrompt()
{
	gotoxy(28, 12);
	printf("�X�T�T�T�T�T�T�T�T�[\n");
	gotoxy(28, 13);
	printf("�U���������ʼ��Ϸ�U\n");
	gotoxy(28, 14);
	printf("�^�T�T�T�T�T�T�T�T�a\n");
	gotoxy(1, 1);
	_getch();
	system("cls");
}

void PrintChess()
{
	int nStatus;
	int i;

	system("cls");

	// ��������к�
	char cA = 'A';
	printf("\n\n\n\t\t       ");
	for (i = 0; i < MAX; i++)
		printf("%C ", cA + i);
	printf("\n");

	//�����������
	printf("\t\t    ��");
	for (i = 0; i < MAX; i++)
		printf("��");
	printf("��\n");

	// �������
	for (int row = 0; row < MAX; row++)
	{
		for (int line = -1; line < MAX; line++)
		{
			if (line == -1)
			{
				// ���������߽�
				printf("\t\t  %02d��", row + 1);
				continue;
			}

			// �������״̬
			nStatus = GetStatus(row, line);
			// ���ݲ�ͬ��״ֵ̬�����Ʋ�ͬ��ͼ��
			
			if (nStatus == STATUS_BLANK)// �˴�Ϊ��
			{
				printf(CHESS_BLANK);
			}
			else if (nStatus == STATUS_WHITE)// �˴�Ϊ����
			{
				printf(CHESS_WHITE);
			}
			else if (nStatus == STATUS_BLACK)// �˴�Ϊ���� 
			{
				printf(CHESS_BLACK);
			}
		} // for (int line = -1; line < MAX; line++)
		printf("��%02d\n", row + 1);
	} // for (int row = 0; row < MAX; row++)

	//�����������
	printf("\t\t    ��");
	for (i = 0; i < MAX; i++)
		printf("��");
	printf("��\n");

	// ��������к�(��)
	cA = 'A';
	printf("\t\t       ");
	for (i = 0; i < MAX; i++)
		printf("%C ", cA + i);
	printf("\n");
}


void PlayGame()
{
	int nRow = -1;						// ��������
	int nCol = -1;						// ��������
	int nStep = 0;						// ���ӵĲ���

	// ��ʼ����Ϸ����
	InitStatus();

	// ��������
	PrintChess();

	// �����ʼ��ʾ
	PrintPrompt();

	// ��������
	PrintChess();

	//��ʼ���壬ʹ��do��while��������һ�ӣ��ٽ��м���Ƿ��ʤ
	do {
		// ����û���������
		InputPoint(&nRow, &nCol, nStep % 2);

		// ���������״̬
		SetStatus(nRow, nCol, nStep % 2);

		// ��������
		PrintChess();

		//��������
		nStep++;

	} while (1);						// ѭ�����ӣ�����ʤʱ�������ѭ��

	
}
