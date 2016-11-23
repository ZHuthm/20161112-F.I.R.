#ifndef _MODAL_H_
#define _MODAL_H_

// ������״̬����

enum PointStatus
{
	BLANK = -1,		// blank
	BLACK = 0,		// black
	WHITE = 1		// white
};

// ���������
typedef struct Point
{
	int row;				// �к�
	int col;				// �к�
	int status;				// ��ǰ���״ֵ̬��ȡֵ��ӦPointStatus����
}Point;

// ��������
typedef struct Rank
{
	char name[64];			// ���ID
	int step;				// ʤ��ʱ���õĲ���
}Rank;

#endif