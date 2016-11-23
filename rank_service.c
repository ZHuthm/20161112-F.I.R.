#include "rank_service.h"
#include "rank_file.h"
#include "model.h"

Rank AsrRanks[10];
int NRankSize = 0;

int JudgeOrder(const int nStep)
{
	// ����Ԫ�ر���ʱ��������
	int nIndex = 0;

	// �ҵ���һ�����ڸò�������ң�������ҵ�����Ϊ�ҵ�����ҵ�ǰһ��
	while (nIndex < NRankSize)
	{
		if (AsrRanks[nIndex].step > nStep)
		{
			break;
		}
		nIndex++;
	}

	// ��������������ֵ�ϴ�1
	return nIndex + 1;
}

void InsertRank(const int nPostion, const Rank srRank)
{
	// Ԫ������������
	int nIndex = NRankSize;

	// �������Ϊ���һ��Ԫ��ʱ��ֱ�Ӹ���ԭ���ݣ����򣬽�����Ԫ�����κ���һλ
	if (nPostion < 9)
	{
		while (nIndex > nPostion)
		{
			AsrRanks[nIndex] = AsrRanks[nIndex - 1];
			nIndex--;
		}
	}

	// �ڲ��������µ�Ԫ��
	AsrRanks[nPostion] = srRank;

	if (NRankSize < 10)
	{
		// ������������
		NRankSize++;
	}
}

void SaveRanks()
{
	WriteRanklist(AsrRanks,NRankSize);
}

int GetRankSize()
{
	return NRankSize;
}

int GetRanks(Rank* psrRanks, const int nMaxSize)
{
	// ����������
	int nIndex = 0;

	// ѭ����ȫ�ֱ�����ȡ�����ݣ��ŵ���ʱ��ŵ�������
	for (nIndex = 0; nIndex < NRankSize&&nIndex < nMaxSize; nIndex++)
	{
		psrRanks[nIndex] = AsrRanks[nIndex];
	}

	// �����ŵ���������Ϊ��ȷ��������Ҹ���
	return nIndex;
}

void InitRanks()
{
	//��ȡ�������飬��ø���
	NRankSize = ReadRanklist(AsrRanks, 10);
}

