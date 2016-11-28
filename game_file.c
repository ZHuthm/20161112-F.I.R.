#include "game_file.h"

void WriteGameInfo(int nStep, int aChessStatus[MAX][MAX])
{
	FILE* pfGame = NULL;
	int err = 0;
	
	err = fopen_s(&pfGame, "gamesaver.dat", "wb");

	// ���ļ�����
	if (err != 0)
	{
		printf("�ļ���ʧ�ܣ�");
		getchar();
		return FALSE;
	}

	fprintf_s(pfGame, "Step:%d\n", nStep);

	int i = 0;
	int j = 0;
	// д��������Ϣ
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			fprintf_s(pfGame, "%d\n", aChessStatus[i][j]);
		}

	}

	// �ر��ļ�
	fclose(pfGame);
}

void ReadGameInfo(int *nStep, int aChessStatus[MAX][MAX])
{
	FILE* pfGame = NULL;
	int err = 0;

	err = fopen_s(&pfGame, "gamesaver.dat", "rb");

	// ���ļ�����
	if (err != 0)
	{
		printf("�ļ���ʧ�ܣ�");
		getchar();
		return FALSE;
	}

	fscanf_s(pfGame, "Step:%d\n", nStep);

	int i = 0;
	int j = 0;

	// д��������Ϣ
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
		{
			fscanf_s(pfGame, "%d\n", &aChessStatus[i][j]);
		}

	// �ر��ļ�
	fclose(pfGame);
}

