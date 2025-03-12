#include <stdio.h>
#include <math.h>

#pragma warning(disable: 4326 4996 6031)

void main()
{
	while (1) {
		printf("Á¤¼ö ? ");
		int nNmbr;
		scanf("%d", &nNmbr);
		if (nNmbr <= 0)
			break;
		int Lyons(int nNmbr);
		int Simple(int nNmbr);
		int Spence(int nNmbr);
		int Toja(int nNmbr);
		printf(" Lyons: %d\n", Lyons(nNmbr));
		printf("Simple: %d\n", Simple(nNmbr));
		printf("Spence: %d\n", Spence(nNmbr));
		printf("  Toja: %d\n", Toja(nNmbr));
		putchar('\n');
	}
	printf("Bye, ...\n");
}

int Lyons(int nNmbr)
{
	int nGroup[3] = { 0 };
	for (int i = 0; nNmbr; nNmbr /= 100, i = (i + 1) % 3)
		nGroup[i] = (nGroup[i] + nNmbr % 100) % 7;
	nNmbr = (nGroup[2] * 10 + nGroup[1] - nGroup[1] * 10 - nGroup[0]) % 7;
	return nNmbr == 0;
}

int Simple(int nNmbr)
{
	static int nRems[] = { 1, 3, 2, 6, 4, 5 };
	if (nNmbr < 14)
		return nNmbr == 7;
	int nSum = 0;
	for (int nNdx = 0; nNmbr; nNdx = (nNdx + 1) % 6, nNmbr /= 10)
		nSum += nNmbr % 10 * nRems[nNdx];
	return Simple(nSum);
}

int Spence(int nNmbr)
{
	if (nNmbr < 7)
		return nNmbr == 0;
	nNmbr = nNmbr / 10 - nNmbr % 10 * 2;
	nNmbr -= (nNmbr < -6) * nNmbr / 7 * 7;
	return Spence(nNmbr);
}

int Toja(int nNmbr)
{
	if (nNmbr < 7)
		return nNmbr == 0;
	int nSum = 0;
	for (int t = 0; nNmbr; nNmbr /= -100)
		nSum = nSum * 10 + (t = nNmbr % 100 % 7) + (t < 0) * 7;
	return Toja(nSum);
}
