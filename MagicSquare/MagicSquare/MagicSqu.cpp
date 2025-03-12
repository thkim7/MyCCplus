#include <stdio.h>
#include <math.h>

#pragma warning(disable : 4326 4996 6031 6262)

#define	N	100

void main()
{
	void MakeMagicSquare(int nMagicSqr[][N], int nN);
	void ShowMagicSquare(int nMagicSqr[][N], int nN);
	void CheckMagicSquare(int nMagicSqr[][N], int nN);

	int nN;
	int nMagicSqr[N][N];
	while (1) {
		printf("? ");
		scanf("%d", &nN);
		if (nN <= 2 || nN > N)
			break;
		MakeMagicSquare(nMagicSqr, nN);
		ShowMagicSquare(nMagicSqr, nN);
		CheckMagicSquare(nMagicSqr, nN);
		putchar('\n');
	}
	printf("Bye, ....\n");
}

void MakeMagicSquare(int nMagicSqr[][N], int nN)
{
	void InitFormat(int nN);
	void OddMagicSquare(int nSqr[][N], int nN, int nORow = 0, int nOCol = 0, int nBgn = 1);
	void SnglyEvenMagicSquare(int nMagicSqr[][N], int nN);
	void DblyEvenMagicSquare(int nMagicSqr[][N], int nN);

	InitFormat(nN);
	if (nN % 2)
		OddMagicSquare(nMagicSqr, nN);
	else if (nN % 4)
		SnglyEvenMagicSquare(nMagicSqr, nN);
	else
		DblyEvenMagicSquare(nMagicSqr, nN);
}

static char sFmt0[] = "%1d ";
static char sFmt1[] = "행 %1d";
static char sFmt2[] = "열 %1d";
static char sFmt3[] = "대 %1c";

void ShowMagicSquare(int nMagicSqr[][N], int nN)
{
	printf("\n[마방진]\n");
	for (int nRow = 0; nRow < nN; nRow++) {
		for (int nCol = 0; nCol < nN; nCol++)
			printf(sFmt0, nMagicSqr[nRow][nCol]);
		putchar('\n');
	}
}

void CheckMagicSquare(int nMagicSqr[N][N], int nN)
{
	void CheckMagicSquareRow(int nMagicSqr[N][N], int nN);
	void CheckMagicSquareCol(int nMagicSqr[N][N], int nN);
	void CheckMagicSquareDgl(int nMagicSqr[N][N], int nN, int nDir);

	CheckMagicSquareRow(nMagicSqr, nN);
	CheckMagicSquareCol(nMagicSqr, nN);
	printf("\n[대각선 검사]\n");
	CheckMagicSquareDgl(nMagicSqr, nN, '\\');
	CheckMagicSquareDgl(nMagicSqr, nN, '/');
}

void InitFormat(int nN)
{
	sFmt0[1] = (int)log10(nN * nN) + 0x31;
	sFmt1[4] = sFmt2[4] = sFmt3[4] = (int)log10(nN - 1) + 0x31;
}

void CheckMagicSquareRow(int nMagicSqr[N][N], int nN)
{
	printf("\n[행 검사]\n");
	for (int nRow = 0; nRow < nN; nRow++) {
		printf(sFmt1, nRow);
		int nSum = 0;
		for (int nCol = 0; nCol < nN; nCol++) {
			printf("%c ", nCol ? '+' : ':');
			printf(sFmt0, nMagicSqr[nRow][nCol]);
			nSum += nMagicSqr[nRow][nCol];
		}
		printf("= %d\n", nSum);
	}
}

void CheckMagicSquareCol(int nMagicSqr[N][N], int nN)
{
	printf("\n[열 검사]\n");
	for (int nCol = 0; nCol < nN; nCol++) {
		printf(sFmt2, nCol);
		int nSum = 0;
		for (int nRow = 0; nRow < nN; nRow++) {
			printf("%c ", nRow ? '+' : ':');
			printf(sFmt0, nMagicSqr[nRow][nCol]);
			nSum += nMagicSqr[nRow][nCol];
		}
		printf("= %d\n", nSum);
	}
}

void CheckMagicSquareDgl(int nMagicSqr[N][N], int nN, int nDir)
{
	int nSum = 0, nDgnl = nDir == '/';
	int nCol = nDgnl * (nN - 1), nDelta = 1 - nDgnl * 2;
	printf(sFmt3, nDir);
	for (int nRow = 0; nRow < nN; nRow++, nCol += nDelta) {
		printf("%c ", nRow ? '+' : ':');
		printf(sFmt0, nMagicSqr[nRow][nCol]);
		nSum += nMagicSqr[nRow][nCol];
	}
	printf("= %d\n", nSum);
}

void OddMagicSquare(int nMagicSqr[][N], int nN, int nOrgRow, int nOrgCol, int nBgn)
{
	void InitMagicSquare(int nMagicSqr[][N], int nN, int nOrgRow, int nOrgCol);
	InitMagicSquare(nMagicSqr, nN, nOrgRow, nOrgCol);
	int nRow = 0, nCol = nN / 2, nCell = nN * nN;
	nMagicSqr[nOrgRow + nRow][nOrgCol + nCol] = nBgn;
	for (int i = 1; i < nCell; i++) {
		nRow = (nRow - 1 + nN) % nN;
		nCol = (nCol + 1) % nN;
		if (nMagicSqr[nOrgRow + nRow][nOrgCol + nCol]) {
			nRow = (nRow + 2) % nN;
			nCol = (nCol - 1 + nN) % nN;
		}
		nMagicSqr[nOrgRow + nRow][nOrgCol + nCol] = nBgn + i;
	}
}

void DblyEvenMagicSquare(int nMagicSqr[][N], int nN)
{
	for (int nRow = 0, k = 1, nSqr = nN * nN + 1; nRow < nN; nRow++)
		for (int nCol = 0; nCol < nN; nCol++, k++)
			nMagicSqr[nRow][nCol] = (nRow - nCol) % 4 && (nRow + nCol + 1) % 4 ? k : nSqr - k;
}

//
// 이 이후부터는 그냥 참고만 하기 바랍니다.
//
void SnglyEvenMagicSquare(int nMagicSqr[][N], int nN)
{
	static int nOrg[] = { 0, 3, 1, 2 };
	int nH = nN / 2;
	int nSqr = nH * nH;
	for (int i = 0, nBgn = 1; i < 4; i++, nBgn += nSqr)
		OddMagicSquare(nMagicSqr, nH, nOrg[i] / 2 * nH, nOrg[i] % 2 * nH, nBgn);
	int nQ = nH / 2;
	void SwitchHalf(int nMagicSqr[][N], int nCol, int nHalf);
	for (int nCol = 0; nCol < nQ; nCol++)
		SwitchHalf(nMagicSqr, nCol, nH);
	for (int nCol = nH + nQ + 2; nCol < nN; nCol++)
		SwitchHalf(nMagicSqr, nCol, nH);
	void Swap(int& x, int& y);
	Swap(nMagicSqr[nQ][0], nMagicSqr[nQ + nH][0]);		// Left Center at 0-th SQR <--> Left Center at 2-th SQR
	Swap(nMagicSqr[nQ][nQ], nMagicSqr[nQ + nH][nQ]);	// Center cell at 0-th SQR <--> Center cell at 2-th SQR
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

void InitMagicSquare(int nMagicSqr[][N], int nN, int nOrgRow, int nOrgCol)
{
	for (int nRow = 0; nRow < nN; nRow++)
		for (int nCol = 0; nCol < nN; nCol++)
			nMagicSqr[nOrgRow + nRow][nOrgCol + nCol] = 0;
}
