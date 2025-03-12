#include <stdio.h>

#pragma warning(disable: 4326 4996 6031)

void main()
{
	while (true) {
		int nCtr;
		printf("Disks ? ");
		scanf("%d", &nCtr);			// 옮기는 탑의 층을 입력 받는다.
		if (nCtr <= 0)
			break;
		void hanoi(int nDisk, int nFrom, int nTo);
		hanoi(nCtr, 1, 2);			// 탑을 1에서 2로 옮기시요.
	}
}

void hanoi(int nDisk, int nFrom, int nTo)
{	// Terminal condition: nDisk == 1, 그냥 이동한다
	if (nDisk == 1)
		printf("%d --> %d\n", nFrom, nTo);
	else {
		int nTemp = 6 - nFrom - nTo;
		hanoi(nDisk - 1, nFrom, nTemp);
		hanoi(1, nFrom, nTo);
		hanoi(nDisk - 1, nTemp, nTo);
	}
}
