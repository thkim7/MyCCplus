#include <stdio.h>
#include <math.h>

#define	N	100

#pragma warning( disable : 4996 )

void main()
{
	void makeMagicSquare(int nMagicSqr[][N], int nN);
	void showMagicSquare(int nMagicSqr[][N], int nN);
	void checkMagicSquare(int nMagicSqr[][N], int nN);

	int nN;
	int nMagicSqr[N][N];
	while (1) {
		printf("? ");
		scanf("%d", &nN);
		if (nN <= 2 || nN > N)
			break;
		makeMagicSquare(nMagicSqr, nN);
		showMagicSquare(nMagicSqr, nN);
		checkMagicSquare(nMagicSqr, nN);
		putchar('\n');
	}
	printf("Bye, ....\n");
}

void makeMagicSquare(int nMagicSqr[][N], int nN)
{
	void InitMagicSquare(int nMagicSqr[][N], int nN);
	void OddMagicSquare(int nMagicSqr[][N], int nN, int nOrgRow = 0, int nOrgCol = 0, int nBgn = 0);
	void DblyEvenMagicSquare(int nMagicSqr[][N], int nN);
	void SnglyEvenMagicSquare(int nMagicSqr[][N], int nN);

	InitMagicSquare(nMagicSqr, nN);
	if (nN % 2)
		OddMagicSquare(nMagicSqr, nN);
	else if (nN % 4)
		SnglyEvenMagicSquare(nMagicSqr, nN);
	else
		DblyEvenMagicSquare(nMagicSqr, nN);
}

static char sFmt1[] = "행 %1d";
static char sFmt2[] = "열 %1d";
static char sFmt3[] = "대 %1c";
static char sFmt4[] = "%1d ";

void InitMagicSquare(int nMagicSqr[][N], int nN)
{
	for (int nRow = 0; nRow < nN; nRow++)
		for (int nCol = 0; nCol < nN; nCol++)
			nMagicSqr[nRow][nCol] = 0;
	sFmt1[4] = sFmt2[4] = sFmt3[4] = (int)log10(nN - 1) + 0x31;
	sFmt4[1] = (int)log10(nN * nN) + 0x31;
}

void OddMagicSquare(int nMagicSqr[][N], int nN, int nOrgRow, int nOrgCol, int nBgn)
{
	int nRow = 0, nCol = nN / 2, nCell = nN * nN;
	nMagicSqr[nRow + nOrgRow][nCol + nOrgCol] = nBgn + 1;
	for (int i = 2; i <= nCell; i++) {
		int nPrvRow = nRow, nPrvCol = nCol;
		nRow = (nRow - 1 + nN) % nN;
		nCol = (nCol + 1) % nN;
		if (nMagicSqr[nRow + nOrgRow][nCol + nOrgCol]) {
			nRow = (nPrvRow + 1) % nN;
			nCol = nPrvCol;
		}
		nMagicSqr[nRow + nOrgRow][nCol + nOrgCol] = nBgn + i;
	}
}

void DblyEvenMagicSquare(int nMagicSqr[][N], int nN)
{
	for (int nRow = 0, nNmbr = 1, nCell = nN * nN + 1; nRow < nN; nRow++)
		for (int nCol = 0; nCol < nN; nCol++, nNmbr++)
			nMagicSqr[nRow][nCol] = ((nRow - nCol) % 4 && (nRow + nCol + 1) % 4) ? nNmbr : nCell - nNmbr;
}


void SnglyEvenMagicSquare(int nMagicSqr[][N], int nN)
{
	static int nOrg[][2] = { { 0, 0 },{ 1, 1 },{ 0, 1 },{ 1, 0 } };
	int nH = nN / 2;
	int nSqr = nH * nH;
	for (int i = 0; i < 4; i++)
		OddMagicSquare(nMagicSqr, nH, nOrg[i][0] * nH, nOrg[i][1] * nH, i * nSqr);
	int nQ = nH / 2;
	void SwitchHalf(int nMagicSqr[][N], int nCol, int nHalf);
	for (int nCol = 0; nCol < nQ; nCol++)
		SwitchHalf(nMagicSqr, nCol, nH);
	for (int nCol = nH + nQ + 2; nCol < nN; nCol++)
		SwitchHalf(nMagicSqr, nCol, nH);
	void Swap(int& x, int& y);
	Swap(nMagicSqr[nQ][0], nMagicSqr[nQ + nH][0]);		
	Swap(nMagicSqr[nQ][nQ], nMagicSqr[nQ + nH][nQ]);
}

void SwitchHalf(int nMagicSqr[][N], int nCol, int nHalf)
{
	void Swap(int& x, int& y);
	for (int nRow = 0; nRow < nHalf; nRow++)
		Swap(nMagicSqr[nRow][nCol], nMagicSqr[nRow + nHalf][nCol]);
}

void Swap(int& x, int& y)
{
	int t = x;
	x = y;
	y = t;
}

void showMagicSquare(int nMagicSqr[][N], int nN)
{
	char FMTsqr[] = "%2d ";
	FMTsqr[1] = (int)log10(nN * nN) + 0x31;
	printf("\n[마방진]\n");
	for (int nRow = 0; nRow < nN; nRow++) {
		for (int nCol = 0; nCol < nN; nCol++)
			printf(FMTsqr, nMagicSqr[nRow][nCol]);
		putchar('\n');
	}
}

void checkMagicSquare(int nMagicSqr[N][N], int nN)
{
	void checkMagicSquareRow(int nMagicSqr[N][N], int nN);
	void checkMagicSquareCol(int nMagicSqr[N][N], int nN);
	void checkMagicSquareDgl(int nMagicSqr[N][N], int nN, int nDir);

	checkMagicSquareRow(nMagicSqr, nN);
	checkMagicSquareCol(nMagicSqr, nN);
	printf("\n[대각선 검사]\n");
	checkMagicSquareDgl(nMagicSqr, nN, '\\');
	checkMagicSquareDgl(nMagicSqr, nN, '/');
}

void checkMagicSquareRow(int nMagicSqr[N][N], int nN)
{
	printf("\n[행 검사]\n");
	for (int nRow = 0; nRow < nN; nRow++) {
		printf(sFmt1, nRow);
		int nSum = 0;
		for (int nCol = 0; nCol < nN; nCol++) {
			printf("%c ", nCol ? '+' : ':');
			printf(sFmt4, nMagicSqr[nRow][nCol]);
			nSum += nMagicSqr[nRow][nCol];
		}
		printf("= %d\n", nSum);
	}
}

void checkMagicSquareCol(int nMagicSqr[N][N], int nN)
{
	printf("\n[열 검사]\n");
	for (int nCol = 0; nCol < nN; nCol++) {
		printf(sFmt2, nCol);
		int nSum = 0;
		for (int nRow = 0; nRow < nN; nRow++) {
			printf("%c ", nRow ? '+' : ':');
			printf(sFmt4, nMagicSqr[nRow][nCol]);
			nSum += nMagicSqr[nRow][nCol];
		}
		printf("= %d\n", nSum);
	}
}

void checkMagicSquareDgl(int nMagicSqr[N][N], int nN, int nDir)
{
	int nSum = 0, nDgnl = nDir == '/';
	int nCol = nDgnl * (nN - 1), nDelta = 1 - nDgnl * 2;
	printf(sFmt3, nDir);
	for (int nRow = 0; nRow < nN; nRow++, nCol += nDelta) {
		printf("%c ", nRow ? '+' : ':');
		printf(sFmt4, nMagicSqr[nRow][nCol]);
		nSum += nMagicSqr[nRow][nCol];
	}
	printf("= %d\n", nSum);
}
