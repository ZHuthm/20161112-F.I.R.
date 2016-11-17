#include "menu.h"


HANDLE hout;

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
	printf("\t\t\t        ��ʼ��Ϸ\n");
	printf("\t\t\t        �������\n");
	printf("\t\t\t        ���а�\n");
	printf("\t\t\t        �鿴����\n");
	printf("\t\t\t        ��������\n");
	printf("\t\t\t        �˳�\n");
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