#include "game_service.h"
#include "global.h"
#include <windows.h>

int AnChessStatus[MAX][MAX];

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
		gotoxy(17,24);
		//�Դ˱�ʶ����ʾ�û�������
		printf("==========================================\n");
		//����ִ�ӷ�����ʾ�û���������
		if (nColor == 0)					// �ڷ�ִ��
		{
			gotoxy(20, 25);
			printf("���ӡ��£������������ţ��磺A1����");
		}
		else if (nColor == 1)				// �׷�ִ��
		{
			gotoxy(20, 25);
			printf("���ӡ��£������������ţ��磺A1����");
		}

		// ����û����������
		//getchar();
		fgets(acPoint, 8, stdin);

		*pnCol = toupper(acPoint[0]) - 'A';	// ���ַ�ת��Ϊ��дӢ����ĸ,��Ӧ��ά����ĵ�һ���±�Ϊ0
		*pnRow = atoi(&acPoint[1]) - 1;		// �ַ����ĵڶ�����ĸ��Ϊ���֣�ʹ��atoi��������ת��

		// �ж�������кź��к��Ƿ���Ч
		if (*pnRow < 0 || *pnRow>MAX-1 || *pnCol < 0 || *pnCol >MAX-1)
		{
			legal = 0;						// �Ƿ�����
			gotoxy(32, 26);
			printf("������ʧ�ܡ�");
			gotoxy(26, 27);
			printf("���겻���ڣ���ȷ�����룡\n");
			continue;
		}

		// ���������״ֵ̬
		nStatus = GetStatus(*pnRow, *pnCol);

		//�ж�״̬
		if (nStatus != STATUS_BLANK)		// ��״̬��Ϊ���ǣ���������
		{
			legal = 0;						// �Ƿ�����
			// ��ǰλ���Ѿ��������ӣ���ʾ�û�
			gotoxy(32, 26);
			printf("������ʧ�ܡ�");
			gotoxy(26, 27);
			printf("%02d��%c���������ӣ��������ӣ�\n", *pnCol+1, *pnRow+'A');
			continue;
		}

		// ����������Ч���Ҹ�����״̬ΪBLANK����Ϊ�Ϸ�λ��
		legal = 1;							// �������Ϸ�

	} while (legal==0);						// ����Ƿ�����Ҫ��������

}

void PrintBound()
{
	int i;
	gotoxy(13, 2);
	printf("�X");
	for ( i = 0; i < 30; i++)
	{
		printf("�T");
	}
	printf("�[");
	for ( i = 0; i < 25; i++)
	{
		gotoxy(13, 3 + i);
		printf("�U");
		gotoxy(75, 3 + i);
		printf("�U");
	}
	gotoxy(13, 28);
	printf("�^");
	for (i = 0; i < 30; i++)
	{
		printf("�T");
	}
	gotoxy(75, 28);
	printf("�a");
	
	
}

void PrintPrompt()
{
	gotoxy(28, 12);
	printf("�X�T�T�T�T�T�T�T�T�[");
	gotoxy(28, 13);
	printf("�U���������ʼ��Ϸ�U");
	gotoxy(28, 14);
	printf("�^�T�T�T�T�T�T�T�T�a");
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
	int nResult;

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
		// ����û���������
		InputPoint(&nRow, &nCol, nStep % 2);

		// ���������״̬
		SetStatus(nRow, nCol, nStep % 2);

		// ��������
		PrintChess();

		//��������
		nStep++;

		// �ж����
		nResult = JudgeGame(nRow, nCol);
	} while (nResult == JUDGE_CONTINUE);	// ѭ�����ӣ�����ʤʱ�������ѭ��

	if (nResult == JUDGE_WIN)
	{
		PrintWinner((nStep - 1) % 2);	// ���ʤ����Ϣ
	}
	else if (nResult == JUDGE_DRAW)		// ���������Ϣ
	{
		PrintDraw();
	}
	
}

int JudgeDraw()
{
	int i, j;
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			if (AnChessStatus[i][j] == STATUS_BLANK)
				return FALSE;
	return TRUE;
	return 0;
}

int JudgeGame(const int nRow, const int nCol)
{
	// �����ж��Ƿ��ʤ
	// ��������������¼������ͬ��������
	int nCount;	

	// ��ȡ���ӵı�׼״̬,�����ж�
	const int STANDARD = AnChessStatus[nRow][nCol];

	// �����ж�
	nCount = JudgeHorizontal(nRow, nCol, STANDARD);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// �����ж�
	nCount = JudgeVertical(nRow, nCol, STANDARD);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// �Խ����ж�I�������µ����ϣ�
	nCount = JudgeHyperphoria(nRow, nCol, STANDARD);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// �Խ����ж�II�������ϵ����£�
	nCount = JudgeHypophoria(nRow, nCol, STANDARD);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// ��
	// �ж������Ƿ�����
	if (JudgeDraw() == TRUE)
		return JUDGE_DRAW;
	
	// û��ʤ��������δ������Ϸ����
	return JUDGE_CONTINUE;
}

int JudgeHorizontal(const nRow, const nCol, const int nStandard)
{
	int i, j;
	int counter = 1;		// ����ͬɫ����������
	j = nCol;

	//����(����)
	i = nRow-1;
	while (i >= 0)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// ���ӵ����ϱ���������ͬɫ������+1
			i--;			// �������ϱ���
		}
		else
			break;			// ������ͬɫ�������ϱ���
	}

	//�������£�
	i = nRow + 1;
	while (i < MAX)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// ���ӵ����±���������ͬɫ������+1
			i++;			// �������±���
		}
		else
			break;			// ������ͬɫ�������±���
	}

	return counter;
}

int JudgeVertical(const nRow, const nCol, const int nStandard)
{
	int i, j;
	int counter = 1;		// ����ͬɫ����������
	i = nRow;

	//����(����)
	j = nCol - 1;
	while (j >= 0)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// ���ӵ��������������ͬɫ������+1
			j--;			// �����������
		}
		else
			break;			// ������ͬɫ�����������
	}

	//�������ң�
	j = nCol + 1;
	while (j < MAX)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// ���ӵ��������������ͬɫ������+1
			j++;			// �������ұ���
		}
		else
			break;			// ������ͬɫ�������ұ���
	}

	return counter;
}

int JudgeHyperphoria(const nRow, const nCol, const int nStandard)
{

	int i, j;
	int counter = 1;		// ����ͬɫ����������
	

	//�Խ���(�L������)
	i = nRow - 1;
	j = nCol + 1;
	while (j < MAX&&i >= 0)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// ���ӵ������±���������ͬɫ������+1
			j++;			// ���������±���
			i--;
		}
		else
			break;			// ������ͬɫ���������±���
	}

	//�Խ���(�J������)
	i = nRow + 1;
	j = nCol - 1;
	while (j >= 0 && i < MAX)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// ���ӵ������ϱ���������ͬɫ������+1
			i++;			// ���������ϱ���
			j--;
		}
		else
			break;			// ������ͬɫ���������ϱ���
	}

	return counter;
}

int JudgeHypophoria(const nRow, const nCol, const int nStandard)
{

	int i, j;
	int counter = 1;		// ����ͬɫ����������


	//�Խ���(�I������)
	i = nRow - 1;
	j = nCol - 1;
	while (j >= 0 && i >= 0)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// ���ӵ������ϱ���������ͬɫ������+1
			j--;			// ���������ϱ���
			i--;
		}
		else
			break;			// ������ͬɫ���������ϱ���
	}

	//�Խ���(�K������)
	i = nRow + 1;
	j = nCol + 1;
	while (i < MAX&&j < MAX)
	{
		if (AnChessStatus[i][j] == nStandard)
		{
			counter++;		// ���ӵ������±���������ͬɫ������+1
			i++;			// ���������±���
			j++;
		}
		else
			break;			// ������ͬɫ���������±���
	}

	return counter;
}

void PrintWinner(const int nColor)
{
	if (nColor == 0)					// ��ʾ����ʤ
	{
		gotoxy(28, 12);
		printf("�X�T�T�T�T�T�T�T�T�[");
		gotoxy(28, 13);
		printf("�U��ϲ�����ʤ��U");
		gotoxy(28, 14);
		printf("�^�T�T�T�T�T�T�T�T�a");
		gotoxy(26, 24);

	}
	else if (nColor == 1)				// ��ʾ����ʤ
	{
		gotoxy(28, 12);
		printf("�X�T�T�T�T�T�T�T�T�[");
		gotoxy(28, 13);
		printf("�U��ϲ�����ʤ��U");
		gotoxy(28, 14);
		printf("�^�T�T�T�T�T�T�T�T�a");
		gotoxy(26, 24);

	}

}

void PrintDraw()
{
	gotoxy(28, 12);
	printf("�X�T�T�T�T�T�T�T�T�[");
	gotoxy(28, 13);
	printf("�U  ��������  �U");
	gotoxy(28, 14);
	printf("�^�T�T�T�T�T�T�T�T�a");
	gotoxy(26, 27);
}

