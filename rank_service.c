#include "rank_service.h"
#include "rank_file.h"
#include "model.h"

Node* psnRanklist = NULL;

int JudgeOrder(const int nStep)
{
	Node* psnNode = psnRanklist->next;
	int nOrder = 0;

	// �����б�Ѱ�Ҳ����
	while (psnNode != NULL)
	{
		if (psnNode->rank.step > nStep)
			// �ҵ���һ�����ڸò�������ң�������ҵ�����Ϊ�ҵ�����ҵ�ǰһ��
			break;
		// ָ����һ�����
		psnNode = psnNode->next;
		nOrder++;
	}

	// ��������������ֵ�ϴ�1
	return nOrder + 1;

}

void InsertRank(const int nPostion, const Rank srRank)
{
	// �����ڵ�ָ��
	Node *psnNode = psnRanklist->next;
	// ǰһ�ڵ�ָ��
	Node *psnPreNode = psnRanklist;

	// �ڵ�λ�ü�¼
	int nPos = 0;

	// Ѱ�Ҳ����
	for (nPos = 0; psnNode != NULL&&nPos != nPostion; nPos++)
	{
		psnPreNode = psnNode;
		psnNode = psnNode->next;
	}

	// ����һ��Rank�ռ�
	psnNode = (Node*)malloc(sizeof(Node));

	// ��ʼ���¿��ٵĿռ䣬ȫ����ֵΪ0
	memset(psnNode, 0, sizeof(Node));

	// ������������Ϣ
	psnNode->rank = srRank;

	// ���½ڵ�ָ����һ�ڵ�
	psnNode->next = psnPreNode->next;

	// ��ǰһ�ڵ�ָ���µĽڵ�
	psnPreNode->next = psnNode;

}

void SaveRanks()
{
	// �߼��������ݴ��ݸ����ݴ����ʱ��Ҫ������ת��Ϊ����

	// ����������
	const int nMaxsize = GetRankSize();

	// �����������д���ļ�,��������£���ֵ��nMaxsize���
	int nSize = 0;

	// ����nMaxSize��Rank�ռ䣬������һ��Rank����ռ�
	Rank* psrRanks = (Rank*)malloc(sizeof(Rank)*nMaxsize);

	// ��ʼ���¿ռ�
	memset(psrRanks, 0, sizeof(Rank)*nMaxsize);

	// ����������ݣ����䱣����������
	nSize = GetRanks(psrRanks, nMaxsize); 

	// ������д���ļ���
	WriteRanklist(psrRanks,nSize);

	// �ͷſ��ٵĿռ�
	free(psrRanks);
}

int GetRankSize()
{
	// ָ���һ����ҽڵ㣬��һ����Ҵӵڶ����ڵ㿪ʼ
	Node* psnNode = psnRanklist->next;

	// ����������
	int nIndex = 0;

	// ѭ��������������ڵ�
	while (psnNode != NULL)
	{
		// �Ƶ���һ���ڵ�
		psnNode = psnNode->next;
		// �����ŵ���
		nIndex++;
	}

	// nIndex ��ֵ����Ϊ������ҵĸ���
	return nIndex;
}

int GetRanks(Rank* psrRanks, const int nMaxSize)
{
	// ָ���һ����ҽڵ㣬��һ����Ҵӵڶ����ڵ㿪ʼ
	Node* psnNode = psnRanklist->next;

	// ����������
	int nIndex = 0;

	// ѭ��������������ڵ�
	while (psnNode != NULL&&nIndex < nMaxSize)
	{
		// �����ݴ�ŵ�Ŀ��������
		psrRanks[nIndex] = psnNode->rank;

		// �Ƶ���һ���ڵ�
		psnNode = psnNode->next;
		// �����ŵ���
		nIndex++;
	}

	// �����ŵ���������Ϊ��ȷ��������Ҹ���
	return nIndex;
}

void InitRanks()
{
	// ���ļ��ж�ȡ����Ϊ������ʽ���ڳ�ʼ��������Ϣʱ����Ҫ������ת��Ϊ������

	// ��ȡ�ļ���������ҵĸ���
	const int nMaxSize = GetRanklistCount();

	// Rank����ָ��
	Rank* psrRanks = NULL;
	// ��ȡ������Ҹ�������ֵͨ����nMaxSize���
	int nSize = 0;
	// ��������ֵ
	int nIndex = 0;

	// ��ʼ������ͷ
	if (psnRanklist == NULL)
	{
		// ����һ��Node�ռ�
		psnRanklist = (Node*)malloc(sizeof(Node));
		// ��ʼ��Ϊ��
		memset(psnRanklist, 0, sizeof(Node));
	}

	// ����nMaxSize��Rank����ռ�
	psrRanks = (Rank*)malloc(sizeof(Rank)*nMaxSize);
	// ��ʼ��Ϊ��
	memset(psrRanks, 0, sizeof(Rank)*nMaxSize);

	//��ȡ�������飬��ø���
	nSize = ReadRanklist(psrRanks,nMaxSize);

	// ���β���ڵ�
	for (nIndex = 0; nIndex < nSize; nIndex++)
	{
		// ����ڵ�
		InsertRank(nIndex, psrRanks[nIndex]);
	}

	// �ͷ�����ռ�
	free(psrRanks);
}

void ClearRanks()
{
	// �����ͷŸ��ڵ�Ԫ��
	Node* psnNode = psnRanklist;
	// ����ָ��ǰ��Ҫ�ͷŽڵ�ָ��
	Node* psnCurNode = NULL;

	// ѭ�������ͷ�����
	while (psnNode != NULL)
	{
		// ���浱ǰ��Ҫ�ͷŵĽڵ�
		psnCurNode = psnNode;
		// �Ƶ���һ�ڵ�
		psnNode = psnNode->next;
		// �ͷŵ�ǰ�ڵ�
		free(psnCurNode);
	}
	// ��ָ���ÿ�
	psnRanklist = NULL;
}

