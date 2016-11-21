#include "game_service.h"

int AnChessStatus[MAX][MAX];
HANDLE hout;


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
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			AnChessStatus[i][j] = STATUS_BLANK;
}

int GetStatus(const Point point)
{
	return AnChessStatus[point.row][point.col];
}

void SetStatus(const Point point)
{
	AnChessStatus[point.row][point.col] = point.status;
}

void InputPoint(Point* point)
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
		if (point->status == STATUS_BLACK)					// �ڷ�ִ��
		{
			gotoxy(20, 25);
			printf("���ӡ��£������������ţ��磺A1����");
		}
		else if (point->status == STATUS_WHITE)				// �׷�ִ��
		{
			gotoxy(20, 25);
			printf("���ӡ��£������������ţ��磺A1����");
		}

		// ����û����������
		//getchar();
		fgets(acPoint, 8, stdin);

		point->col = toupper(acPoint[0]) - 'A';	// ���ַ�ת��Ϊ��дӢ����ĸ,��Ӧ��ά����ĵ�һ���±�Ϊ0
		point->row = atoi(&acPoint[1]) - 1;		// �ַ����ĵڶ�����ĸ��Ϊ���֣�ʹ��atoi��������ת��

		// �ж�������кź��к��Ƿ���Ч
		if (point->row < 0 || point->row>MAX-1 || point->col < 0 || point->col >MAX-1)
		{
			legal = 0;						// �Ƿ�����
			gotoxy(32, 26);
			printf("������ʧ�ܡ�");
			gotoxy(26, 27);
			printf("���겻���ڣ���ȷ�����룡\n");
			continue;
		}

		// ���������״ֵ̬
		nStatus = GetStatus(*point);

		//�ж�״̬
		if (nStatus != STATUS_BLANK)		// ��״̬��Ϊ���ǣ���������
		{
			legal = 0;						// �Ƿ�����
			// ��ǰλ���Ѿ��������ӣ���ʾ�û�
			gotoxy(32, 26);
			printf("������ʧ�ܡ�");
			gotoxy(26, 27);
			printf("%02d��%c���������ӣ��������ӣ�\n", point->col +1, point->row +'A');
			continue;
		}

		// ����������Ч���Ҹ�����״̬ΪBLANK����Ϊ�Ϸ�λ��
		legal = 1;							// �������Ϸ�

	} while (legal==0);						// ����Ƿ�����Ҫ��������

}

int InputCoord(Point *point)
{
	gotoxy(17, 24);
	//�Դ˱�ʶ����ʾ�û�������
	printf("==========================================\n");
	if (point->status == STATUS_BLACK)
	{
		gotoxy(20, 25);
		printf("�����ӡ񡿣���ʹ�á���������ѡ������λ�á�");
		gotoxy(23, 6);
		printf("��\b");
	}
	else if (point->status == STATUS_WHITE)
	{
		gotoxy(20, 25);
		printf("�����ӡ𡿣���ʹ�á���������ѡ������λ�á�");
		gotoxy(23, 6);
		printf("��\b");
	}

	COORD coord;			//��Ļ�ϵ�����
	coord.X = 1;
	coord.Y = 1;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	point->col = 0;
	point->row = 0;
	
	char key = 0;

	do
	{
		
		GetConsoleScreenBufferInfo(hout, &csbi);
		coord.X = csbi.dwCursorPosition.X;// �õ�����x��ֵ
		coord.Y = csbi.dwCursorPosition.Y;// �õ�����y��ֵ
		
		if (key != 13)
			key = _getch();
		
		int nStatus = GetStatus(*point);

		switch (key)
		{
		
		//up	 
		case 72:
			if (coord.Y == 5)
			{
				point->row = MAX-1;
				if (nStatus == STATUS_BLANK)
					printf("��");
				else if (nStatus == STATUS_BLACK)
					printf("��");
				else if (nStatus == STATUS_WHITE)
					printf("��");
				coord.Y = MAX + 4;
				SetConsoleCursorPosition(hout, coord);
			}
			else
			{
				point->row--;
				if (nStatus == STATUS_BLANK)
					printf("��");
				else if (nStatus == STATUS_BLACK)
					printf("��");
				else if (nStatus == STATUS_WHITE)
					printf("��");
				coord.Y--;
				SetConsoleCursorPosition(hout, coord);
			}
			break;

		//down
		case 80:
			if (coord.Y == MAX + 4)
			{
				point->row = 0;
				if (nStatus == STATUS_BLANK)
					printf("��");
				else if (nStatus == STATUS_BLACK)
					printf("��");
				else if (nStatus == STATUS_WHITE)
					printf("��");
				coord.Y = 5;
				SetConsoleCursorPosition(hout, coord);
			}
				
			else
			{
				point->row++;
				if (nStatus == STATUS_BLANK)
					printf("��");
				else if (nStatus == STATUS_BLACK)
					printf("��");
				else if (nStatus == STATUS_WHITE)
					printf("��");
				coord.Y++;
				SetConsoleCursorPosition(hout, coord);
			}
			break;
		
		//left
		case 75:
			if (coord.X == 22)
			{
				point->col = MAX - 1;
				if (nStatus == STATUS_BLANK)
					printf("��\b\b");
				else if (nStatus == STATUS_BLACK)
					printf("��\b\b");
				else if (nStatus == STATUS_WHITE)
					printf("��\b\b");
				coord.X = 2 * MAX + 20;
				SetConsoleCursorPosition(hout, coord);
			}
			else
			{
				point->col--;
				if (nStatus == STATUS_BLANK)
					printf("��");
				else if (nStatus == STATUS_BLACK)
					printf("��");
				else if (nStatus == STATUS_WHITE)
					printf("��");
				coord.X -= 2;
				SetConsoleCursorPosition(hout, coord);
			}
			break;
		
		//right
		case 77:
			if (coord.X == 2 * MAX + 20)
			{
				point->col = 0;
				if (nStatus == STATUS_BLANK)
					printf("��\b\b");
				else if (nStatus == STATUS_BLACK)
					printf("��\b\b");
				else if (nStatus == STATUS_WHITE)
					printf("��\b\b");
				coord.X = 22;
				SetConsoleCursorPosition(hout, coord);
			}
			else
			{
				point->col ++;
				coord.X += 2;
				SetConsoleCursorPosition(hout, coord);
				if (nStatus == STATUS_BLANK)
					printf("\b\b��");
				else if (nStatus == STATUS_BLACK)
					printf("\b\b��");
				else if (nStatus == STATUS_WHITE)
					printf("\b\b��");
			}
			break;
		
		//�س�ȷ��
		case 13:
			
			if (point->row < 0 || point->row>MAX - 1 || point->col < 0 || point->col >MAX - 1)
			{
				gotoxy(32, 26);
				printf("������ʧ�ܡ�");
				gotoxy(26, 27);
				printf("���겻���ڣ���ȷ�����룡\n");
				SetConsoleCursorPosition(hout, coord);
				continue;
			}
			//�ж�״̬
			if (GetStatus(*point) != STATUS_BLANK)		// ��״̬��Ϊ���ǣ���������
			{
				// ��ǰλ���Ѿ��������ӣ���ʾ�û�
				gotoxy(32, 26);
				printf("������ʧ�ܡ�");
				gotoxy(26, 27);
				printf("%02d��%c���������ӣ��������ӣ�\n", point->col + 1, point->row + 'A');
				SetConsoleCursorPosition(hout, coord);
				key = _getch();
				continue;
			}
			return 1;

		default:
			continue;
			break;

		}

		if (point->status == STATUS_BLACK)
			printf("��");
		else if (point->status == STATUS_WHITE)
			printf("��");
		SetConsoleCursorPosition(hout, coord);

		key = _getch();

	} while (key != 27);

	char running = 'N';
	do
	{
		gotoxy(28, 12);
		printf("�X�T�T�T�T�T�T�T�T�[");
		gotoxy(28, 13);
		printf("�U ������Ϸ(Y/N)? �U");
		gotoxy(28, 14);
		printf("�^�T�T�T�T�T�T�T�T�a");
		gotoxy(1, 1);
		running = _getch();
		running = toupper(running);	// ���ַ�ת��Ϊ��дӢ����ĸ
	} while (running != 'Y' && running != 'N');

	if (running == 'Y')
		return 0;
	else if(running == 'N')
		return -1;
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
	_getch();
	gotoxy(24, 12);
	printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�[");
	gotoxy(24, 13);
	printf("�U��Ϸ�����пɰ�ESC���˳�!�U");
	gotoxy(24, 14);
	printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�a");
	_getch();
	system("cls");
}

void PrintChess()
{
	int nStatus;
	int i;
	Point point;

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
			point.col = line;
			point.row = row;

			// �������״̬
			nStatus = GetStatus(point);
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

int JudgeGame(Point point)
{
	// �����ж��Ƿ��ʤ
	// ��������������¼������ͬ��������
	int nCount;	

	// ��ȡ���ӵı�׼״̬,�����ж�
	point.status = AnChessStatus[point.row][point.col];

	// �����ж�
	nCount = JudgeHorizontal(point);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// �����ж�
	nCount = JudgeVertical(point);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// �Խ����ж�I�������µ����ϣ�
	nCount = JudgeHyperphoria(point);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// �Խ����ж�II�������ϵ����£�
	nCount = JudgeHypophoria(point);
	if (nCount >= NUMBER_WIN)
		return JUDGE_WIN;

	// ��
	// �ж������Ƿ�����
	if (JudgeDraw() == TRUE)
		return JUDGE_DRAW;
	
	// û��ʤ��������δ������Ϸ����
	return JUDGE_CONTINUE;
}

int JudgeHorizontal(const Point point)
{
	int i, j;
	int counter = 1;		// ����ͬɫ����������
	int nStandard = point.status;
	j = point.col;

	//����(����)
	i = point.row-1;
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
	i = point.row + 1;
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

int JudgeVertical(const Point point)
{
	int i, j;
	int counter = 1;		// ����ͬɫ����������
	int nStandard = point.status;
	i = point.row;

	//����(����)
	j = point.col - 1;
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
	j = point.col + 1;
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

int JudgeHyperphoria(const Point point)
{

	int i, j;
	int counter = 1;		// ����ͬɫ����������
	int nStandard = point.status;


	//�Խ���(�L������)
	i = point.row - 1;
	j = point.col + 1;
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
	i = point.row + 1;
	j = point.col - 1;
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

int JudgeHypophoria(const Point point)
{

	int i, j;
	int counter = 1;		// ����ͬɫ����������
	int nStandard = point.status;


	//�Խ���(�I������)
	i = point.row - 1;
	j = point.col - 1;
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
	i = point.row + 1;
	j = point.col + 1;
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

void PrintWinner(const Point point)
{
	if (point.status == 0)					// ��ʾ����ʤ
	{
		gotoxy(28, 12);
		printf("�X�T�T�T�T�T�T�T�T�[");
		gotoxy(28, 13);
		printf("�U��ϲ�����ʤ��U");
		gotoxy(28, 14);
		printf("�^�T�T�T�T�T�T�T�T�a");
	}
	else if (point.status == 1)				// ��ʾ����ʤ
	{
		gotoxy(28, 12);
		printf("�X�T�T�T�T�T�T�T�T�[");
		gotoxy(28, 13);
		printf("�U��ϲ�����ʤ��U");
		gotoxy(28, 14);
		printf("�^�T�T�T�T�T�T�T�T�a");
	}
	gotoxy(24, 24);
	system("pause");
}

void PrintDraw()
{
	gotoxy(28, 12);
	printf("�X�T�T�T�T�T�T�T�T�[");
	gotoxy(28, 13);
	printf("�U  ��������  �U");
	gotoxy(28, 14);
	printf("�^�T�T�T�T�T�T�T�T�a");
	gotoxy(24, 24);
	system("pause");
}

