#include <stdio.h>

#pragma warning(disable: 4326 4996 6031)

#define N		7
#define	Size	10000000							// 10�� N��

void main()
{
	int  DefineArray(int nArrDesc[]);
	void InitArray(int A[], int nArrDesc[]);
	int  ReadIndex(int nArrDesc[]);
	void PrintIndex(int nArrDesc[]);
	int  Aij(int A[], int nArrDesc[], int& nValue);

	static int Arr[Size];
	int nArrDesc[2 * N + 1];							// �迭 ������
	printf("-1�� �Է��ϸ� �ߴ��ϰ� ���� �ܰ�� �Ѿ��.\n\n");
	int nDim, nVal, nNdx;
	while (1) {
		if ((nDim = DefineArray(nArrDesc)) <= 0)		// �迭�� ������ �а� �迭�� ����
			break;
		InitArray(Arr, nArrDesc);						// ���ǵ� ������� �ʱ�ȭ
		while (1) {
			if (ReadIndex(nArrDesc) == false)			// �迭�� ���ε��� �Է�
				break;
			PrintIndex(nArrDesc);
			if ((nNdx = Aij(Arr, nArrDesc, nVal)) < 0)	// ���ο� �����ϴ� �迭�� ��
				printf(" = %d", nVal);					// �ش� ������ �迭 ��
			else
				printf(" : %d��° ���ο���", nNdx);
			printf("\n\n");
		}
		putchar('\n');
	}
	printf("Bye, ....\n\n");
}

void InitArray(int A[], int nArrDesc[])
{	// ���ǵ� �迭�� ���� ���� ���ο� ���߾� �ʱ�ȭ �Ѵ�.
	int nCtr = 1;
	int nDim = nArrDesc[0];							// �迭�� ����
	int* nBound = nArrDesc + 1;						// �� ������ ũ���
	int* nNdx = nArrDesc + nDim + 1;				// �� ������ ���ε�
	for (int i = 0; i < nDim; i++)
		nCtr *= nBound[i];							// �迭�� ũ�⸦ ���
	for (int i = 0; i < nCtr; i++) {
		int nBase = 1, nSize = 1, nValue = 0;
		for (int j = nDim - 1; j >= 0; j--) {
			nNdx[j] = (i / nSize) % nBound[j];		// �� ������ ����
			nValue += nNdx[j] * nBase;				// �� ���ο� �����ϴ� ��
			nSize *= nBound[j];
			nBase *= 10;
		}
		A[i] = nValue;								// �迭�� �ʱ�ȭ
	}
}

int DefineArray(int nArrDesc[])
{	// �迭�� ������ �� ������ ũ�⵵ �Է¹޾� �迭�� ������ ��ȯ�Ѵ�(����: -1)
	printf("�迭�� ���Ӱ� �����մϴ�.\n");
	printf("�迭�� ����(-1, 1 ~ 7) ? ");
	int nDim;
	scanf("%d", &nDim);
	if (nDim < 0 || nDim > 7)
		return false;
	nArrDesc[0] = nDim;
	printf("\n%d���� �迭�� ũ�⸦ �Է��մϴ�.\n", nDim);
	int* nBound = nArrDesc + 1;							// �� ������ ũ���
	for (int i = 0; i < nDim; i++) {
		int nAgain;
		do {
			printf("int A");
			for (int j = 0; j < i; j++)
				printf("[%d]", nBound[j]);
			printf("[?]");
			for (int j = i + 1; j < nDim; j++)
				printf("[ ]");
			printf(" (-1, 2 ~ 10) ? ");
			scanf("%d", nBound + i);					// �� ������ ũ�� �Է�
			nAgain = nBound[i] < 2 || nBound[i] > 10;	// ������ ũ�� üũ
		} while (nAgain);
	}
	printf("\n\t���ǵ� �迭: int A");
	for (int i = 0; i < nDim; i++)						// ���ǵ� �迭�� ���
		printf("[%d]", nBound[i]);
	printf(";\n\t�˻��� �迭�� ������ �Է��մϴ�.\n\n");
	return nDim;
}

int ReadIndex(int nArrDesc[])
{	// �迭 �����ڿ� ���� �� ������ �Է��Ͽ� T/F�� ��ȯ�Ѵ�.
	int nDim = nArrDesc[0];								// �迭�� ����
	int* nBound = nArrDesc + 1;							// �� ������ ũ���
	int* nNdx = nArrDesc + nDim + 1;					// �� ������ ���ε�
	for (int i = 0; i < nDim; i++) {					// �� ������ ������ �Է�
		printf("\tA");
		for (int j = 0; j < i; j++)
			printf("[%d]", nNdx[j]);
		printf("[?]");
		for (int j = i + 1; j < nDim; j++)
			printf("[ ]");
		printf(" (-1, 0 ~ %d) ? ", nBound[i] - 1);		// ������ ����
		scanf("%d", nNdx + i);							// ���� �Է�
		if (nNdx[i] < 0)								// ������ �����̸�
			return false;								// �ߴ�
	}
	return  true;
}

void PrintIndex(int nArrDesc[])
{
	int nDim = nArrDesc[0];								// �迭�� ����
	int* nNdx = nArrDesc + nDim + 1;					// �� ������ ���ε�
	printf("\tA");
	for (int i = 0; i < nDim; i++)						// �迭�� �� ������ ���
		printf("[%d]", nNdx[i]);
}

int Aij(int A[], int nArrDesc[], int& nValue)
{	// �迭 �����ڿ� �ִ� ���ο� �ش��ϴ� ���Ҹ� nValue�� �����ϰ� ������ ��ȯ�Ѵ�.
	// ���ο� ������ ������ �� ���� ��ȣ(0���� ����)�� ��ȯ�Ѵ�.
	// ������� [1][2][30][4]���� 30�� �����̸� ���ʿ��� 0���� ���� 2�̹Ƿ� 2�� ��ȯ�ȴ�.
	// nArrDesc�� ���� ArrIndex4���� ��� �Ű����� nDim, pNdx, pBound�� ������� ���� ���̴�.
	// nArrDesc[0]:						�迭�� ����				[nDim]
	// nArrDesc[1]  ~  nArrDesc[n]:		�迭�� �� ������ ũ��	[pBound]
	// nArrDesc[n+1] ~ nArrDesc[2n]:	�迭�� �� ������ ����	[pNdx]
	int nDim = nArrDesc[0];								// �迭�� ����
	int* nBound = nArrDesc + 1;							// �� ������ ũ���
	int* nNdx = nArrDesc + nDim + 1;					// �� ������ ���ε�
	int nSize = 1, nSum = 0;
	for (int i = nDim - 1; i >= 0; i--) {
		if (nNdx[i] < 0 || nNdx[i] >= nBound[i])
			return i;
		nSum += nNdx[i] * nSize;
		nSize *= nBound[i];
	}
	nValue = A[nSum];
	return -1;											// ������ return
}
