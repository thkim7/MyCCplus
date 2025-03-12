#define MaxLen 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4326 4996 6031)

void main()
{
	while (1) {
		char str[MaxLen];
		printf("단어 문자열: ");
		gets_s(str);
		if (*str == NULL)
			break;
		int nNdx = 0;
		int nNdxMax = strlen(str) - 1;		// 색인은 0부터 length - 1까지
		while (1) {
			printf("%s의 변화시킬 색인[0~%d] ? ", str, nNdxMax);
			char strNdx[MaxLen];
			gets_s(strNdx);
			nNdx = atoi(strNdx);			// sscanf(strNdx, "%d", &nNdx);
			if (nNdx < 0 || nNdx > nNdxMax)
				break;
			void Perm(char *str, int k, int n);
			Perm(str, nNdx, nNdxMax);
		}
	}
	printf("Bye, ...\n");
}

void swap(char& x, char& y)
{
	char t = x;
	x = y;
	y = t;
}

void Perm(char *str, int k, int n)
{
	if (k == n)
		printf("%s\n", str);
	else {
		for (int i = k; i <= n; i++) {
			swap(str[k], str[i]);		// [k]와 [i]를 바꾸어 고정한다
			Perm(str, k + 1, n);		// k까지 고정이기 때문에 k+1부터 n까지 변화시킨다
			swap(str[k], str[i]);		// 원본으로 복원한다
		}
	}
}
