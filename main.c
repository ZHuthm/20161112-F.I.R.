#include <stdio.h> //printf()����ͷ�ļ�
// stdio "standard buffered input & output
// ���������ı�׼����������õ���׼�����������ʱ����Ҫ�������ͷ�ļ���
#include <windows.h>;
#include <conio.h>

#define MAX 15
const char CHESS_BLANK[4] = "��";

///////////////////////////////////////////////////////
// ��������
/****************************************************
[��������] printMainMenu
[��������] ����˵�������ȡ�û�ѡ��
[��������] ��
[�� �� ֵ] int: �����û�ѡ��
****************************************************/
int printMainMenu(); 

/****************************************************
[��������] printChess
[��������] �������
[��������] ��
[�� �� ֵ] ��
****************************************************/
void printChess();

///////////////////////////////////////////////////////

void gotoxy(int x, int y) //goto���
{
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
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
		system("cls");
		printf("\n\t\t\t����������������������\n");
		printf("\t\t\t����ӭ������������Ϸ��\n");
		printf("\t\t\t����������������������\n");
		nSelect = printMainMenu();
		switch (nSelect)
		{
		case 0:// �˳�

			continue;
		case 1:// ��ʼ��Ϸ
			system("cls");
			printChess();
			gotoxy(28, 12);
			printf("�X�T�T�T�T�T�T�T�T�[\n");
			gotoxy(28, 13);
			printf("�U���������ʼ��Ϸ�U\n");
			gotoxy(28, 14);
			printf("�^�T�T�T�T�T�T�T�T�a\n");
			_getch();
			system("cls");
			printChess();
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
		printf("\n\t\t�������������");
		_getch();
	} while (nSelect != 0);

	// �˳�
	for (int i = 5; i != 0; i--)
	{
		system("cls");
		printf("\n\t\t\t����������������������\n");
		printf(  "\t\t\t��     ��лʹ��!    ��\n");
		printf(  "\t\t\t��    (%d����˳�)   ��\n", i);
		printf(  "\t\t\t����������������������\n");
		Sleep(1000);
	}
	return 0;// �������0���������������˳���
}

int printMainMenu()
{
	// ʹ��char����ǿ����׳��
	int nSelect;

	printf("\n");
	printf("\t\t========================================\n");
	printf("\t\t1.��ʼ��Ϸ\t2.�������\t3.���а�\n");
	printf("\t\t4.�鿴����\t5.��������\t0.�˳�\n");
	printf("\t\t----------------------------------------\n");
	printf("\t\t��ѡ��˵���ţ�");

	// ����û�������
	scanf_s("%d", &nSelect);

	// �������������
	fflush(stdin);

	// �����û�ѡ��Ĳ˵������
	return nSelect;

}

void printChess()
{
	// ��ʼ��������Ϣ
	int a[MAX][MAX] = {0};
	memset(a, -1, sizeof(a)); // ��a��ָ���һ���ڴ��е�ǰsizeof(a)���ֽڵ�����ȫ������Ϊ-1

	/////////////
	//����������ʽ
	a[6][6] = 0;
	a[7][7] = 1;
	/////////////

	// ��������к�
	char cA = 'A';
	printf("\n\n\n\t\t       ");
	for (int i = 0; i < MAX; i++)
		printf("%C ", cA + i);
	printf("\n");
	
	//�����������
	printf("\t\t    ��");
	for (int i = 0; i < MAX; i++)
		printf("��");
	printf("��\n");

	// �������
	for (int row = 0; row < MAX; row++)
	{
		for (int line = -1; line < MAX; line++)
		{
			if (line == -1)
			{
				printf("\t\t  %02d��", row + 1);
				continue;
			}
			else if (a[row][line] == -1)// �˴�Ϊ��
				printf(CHESS_BLANK);
			else if (a[row][line] == 0)// �˴�Ϊ����
				printf("��");
			else // �˴�Ϊ���� 
				printf("��");
		}
		printf("��\n");
	}

	//�����������
	printf("\t\t    ��");
	for (int i = 0; i < MAX; i++)
		printf("��");
	printf("��\n");

}
