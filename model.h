#ifndef _MODAL_H_
#define _MODAL_H_

//������״̬����

enum PointStatus
{
	STATUS_BLANK = -1,		// blank
	STATUS_BLACK = 0,		// black
	STATUS_WHITE = 1		// white
};

// ���������
typedef struct Point
{
	int row;				// �к�
	int col;				// �к�
	int status;				// ��ǰ���״ֵ̬��ȡֵ��ӦPointStatus����
}Point;

#endif