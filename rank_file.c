#include "rank_file.h"

int WriteRanklist(Rank * psrRanks, const int nSize)
{
	FILE* pfRanklist = NULL;
	int nIndex = 0;
	int err;

	// ���ļ�
	err = fopen_s(&pfRanklist,"Ranklist.dat", "wb");

	// ���ļ�����
	if (err != 0)
	{
		printf("�ļ���ʧ�ܣ�");
		getchar();
		return FALSE;
	}

	// д������������
	fprintf(pfRanklist, "TOTALCOUNT%d RANKLIST\n", nSize);

	// ����Rank�ṹ�����飬������ʾ
	for (nIndex = 0; nIndex < nSize; nIndex++)
	{
		psrRanks = &psrRanks[nIndex];

		// д�ļ����ֶ�֮��ʹ�á�=>���ָ�
		fprintf(pfRanklist, "%s=>%d\n", psrRanks->name, psrRanks->step);
	}

	// �ر��ļ�
	fclose(pfRanklist);

	return TRUE;
}

int ReadRanklist(Rank* psrRanks, const int nMaxSize)
{
	FILE* pfRanklist = NULL;		// ���а��ļ�ָ��
	int nSize = 0;					// ������Ҹ���
	int nIndex = 0;					// �����������
	char acBuf[128];				// ����������ļ��ж�ȡ����������
	int err;

	// ���ļ���fopen_s��һ������Ϊָ���ļ���ָ�������ڶ�������Ϊ�ļ���������������Ϊ�򿪷�ʽ
	err = fopen_s(&pfRanklist, "Ranklist.dat", "r");

	// ���ļ�����
	if (err != 0)
	{
		printf("�ļ���ʧ�ܣ�");
		getchar();
		return FALSE;
	}

	// ��ȡ������Ϣ�ĸ���
	fscanf_s(pfRanklist, "TOTALCOUNT%d RANKLIST\n", &nSize);

	// ���ж�ȡ�ļ�������ļ�����10�������ȡ���ļ�β����������ȡ
	for (nIndex = 0; (nIndex < nSize && nIndex < nMaxSize) || !feof(pfRanklist); )
	{
		// ��ȡһ�м�¼���ڸ�ʽ����Ҫ����\n��������ȡ�ľ���һ�м�¼
		fscanf_s(pfRanklist, "%s\n", &acBuf, 128);

		// Ҳ���Բ�ͨ����������
		// fscanf_s(pfRanklist, "%s => %d\n", &srRank.name,&srRank.step); 

		if (strlen(acBuf) > 0)
		{
			psrRanks[nIndex] = ParseRank(acBuf);		// ����������Ϣ��������Ϣ��=> �ָ�
			nIndex++;									// ��ȡ�ɹ�һ�вŽ�����һ��
		}
	}

	// �ر��ļ�
	fclose(pfRanklist);

	// �������ݸ��� 
	return nSize;
}

Rank ParseRank(char * pcBuf)
{
	const char * DELIMS = "=>";		// �ַ����еķָ��
	char *pcTmp = NULL;				// �ַ�ָ����������strtok�����ķ���ֵ��ָ��ָ��������ַ����ĵ�ַ
	char *next_token = NULL;        //���滺�������һ��������ȡ��λ��
	Rank srRank;

	// ��������
	pcTmp = strtok_s(pcBuf, DELIMS, &next_token);
	if (pcTmp != NULL)
	{
		strcpy_s(srRank.name,sizeof(srRank.name), pcTmp);
	}

	// �������Ӳ���
	pcTmp = strtok_s(NULL, DELIMS, &next_token);
	if (pcTmp != NULL)
	{
		srRank.step = atoi(pcTmp);	// ���ַ���ת����������
	}

	return srRank;
}