#include <stdio.h>

#pragma warning(disable: 4996 4326 6001 6031)
#define N	1000


void main()
{
	while (1) {
		printf("? ");
		int n;
		scanf("%d", &n);
		if (n <= 0 || n > N)
			break;
		int SkipErase1(int n);
		int SkipErase2(int n);
		int SkipErase3(int n);
		printf("Simulation: %d\n", SkipErase1(n));
		printf(" Iteration: %d\n", SkipErase2(n));
		printf(" Recursion: %d\n", SkipErase2(n));
		putchar('\n');
	}
	printf("Bye, ...\n");
}

int SkipErase1(int n)
{
	int NextBeadNdx(int nNecklace[], int nNdx, int nMod);
	int nNdx = 1, nNecklace[N];							// ����̸� �迭�� �����Ѵ�(1���� n����)
	for (int i = 1; i <= n; i++)						// ����� n���� ������ 1���� n���� �ʱ�ȭ �Ѵ�
		nNecklace[i] = i;
	for (int i = 1; i < n; i++) {
		nNecklace[nNdx = NextBeadNdx(nNecklace, nNdx, n)] = 0;
		nNdx = NextBeadNdx(nNecklace, nNdx, n);
	}
	return nNecklace[nNdx];
}

int NextBeadNdx(int nNecklace[], int nNdx, int nMod)
{
	int NextNdx(int nNdx, int nMod);
	while (nNecklace[nNdx = NextNdx(nNdx, nMod)] == 0);
	return nNdx;
}

int NextNdx(int nNdx, int nMod)
{
	return nNdx % nMod + 1;
}

int SkipErase2(int n)
{
	int nNecklace[N];									// ����̸� �迭�� �����Ѵ�(0���� n-1����)
	for (int i = 0; i < n; i++)							// ����� n���� ������ 1���� n���� �ʱ�ȭ �Ѵ�
		nNecklace[i] = i + 1;
	while (n > 1) {
		int nHalf = n / 2;
		for (int nTo = 0, nFrom = n % 2 * 2; nTo < nHalf; nTo++, nFrom += 2)
			nNecklace[nTo] = nNecklace[nFrom];
		n = nHalf;
	}
	return nNecklace[0];
}

int SkipErase3(int n)									// ��ȯ �Լ��� �ۼ�
{
	if (n == 1)											// �ߴ�����
		return 1;										// �ܼ��ش�
	return 2 * SkipErase3(n / 2) + n % 2 * 2 - 1;		// �Ϲݱ�Ģ
}
