#include "menu.h"

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
	getchar();

	// �������������
	fflush(stdin);

	// �����û�ѡ��Ĳ˵������
	return nSelect;
	
}