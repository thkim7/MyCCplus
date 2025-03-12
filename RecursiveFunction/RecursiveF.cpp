#include <stdio.h>

#pragma warning(disable: 4326 4996 6031)

#define N	25

void main()
{
	int arr[N];
	for (int i = 0; i < N; i++)
		arr[i] = i + 101;
	while (1) {
		int n;
		printf("n ? ");
		scanf("%d", &n);
		if (n < 0 || n > N)
			break;
		int PrintArrayBwrd1(int a[], int n);
		int PrintArrayBwrd2(int a[], int n);
		int PrintArrayBwrd3(int a[], int n);
		int PrintArrayBwrd4(int a[], int n);
		int PrintArrayBwrd5(int a[], int n);
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintArrayBwrd1(arr, n));
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintArrayBwrd2(arr, n));
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintArrayBwrd3(arr, n));
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintArrayBwrd4(arr, n));
		printf(" Print: ");
		printf("\nReturn: %d\n\n", PrintArrayBwrd5(arr, n));
	}
}

int PrintArrayBwrd1(int a[], int n)		// n-1���� ��ȯ�� ������ 1
{
	/***
	[����]    [0,n-1] --> [0,n-2] n-1
	[�Ϲݱ�Ģ] p(a,n) ::= a[n-1] ���, s=p(a,n-1), s+a[n-1] ��ȯ
	[�������] n�� 1�� ���� --> �����뼱: n==1
	[�ߴ�����] p(a,1) ::= a[0] ���, s=p(a,0), s+a[0] ��ȯ --> n==0, p(a,0) ?
	[�ܼ���]   n==0: ��� x, ��ȯ 0
	***/
	if (n == 0)
		return 0;
	printf("%d ", a[n - 1]);
	int nSum = PrintArrayBwrd1(a, n - 1) + a[n - 1];
	return nSum + a[n -1];
}

int PrintArrayBwrd2(int a[], int n)		// 1���� ������ n-1���� ��ȯ
{
	/***
	[����]    [0,n-1] --> 0 [1, n-1]
	[�Ϲݱ�Ģ] p(a,n) ::= s=p(a+1,n-1), a[0] ���, s+a[0] ��ȯ
	[�������] n�� 1�� ���� --> �����뼱: n==1
	[�ߴ�����] p(a,1) ::= s=p(a+1,0), a[0] ���, s+a[0] ��ȯ --> n==0, p(a,0) ?
	[�ܼ���]   n==0: ��� x, ��ȯ 0
	***/
	if (n == 0)
		return 0;
	int nSum = PrintArrayBwrd1(a + 1, n - 1);
	printf("%d ", a[0]);
	return nSum + a[0];
}

int PrintArrayBwrd3(int a[], int n)		// n/2��, 1��, n/2���� ��ȯ
{
	/***
	[����]     [0,n-1] --> [0,m-1] m [m+1,n-1]
	[�Ϲݱ�Ģ] p(a,n) ::= m=n/2, 
						s=p(a+m+1,n-m-1), a[m] ���, 
						s+=p(a,m), 
						s+a[m] ��ȯ
	[�������] n�� 1/2�� ���� --> �����뼱: n==1
	[�ߴ�����] p(a,1) ::= m=0, 
						s=p(a+1,0), a[m] ���, 
						s+=p(a,0), 
						s+a[0] ��ȯ				--> n==0, p(a,0) ?
	[�ܼ���]   n==0: ��� x, ��ȯ 0
	***/
	if (n == 0)
		return 0;
	int m = n / 2;
	int nSum = PrintArrayBwrd3(a + m + 1, n - m - 1);
	printf("%d ", a[m]);
	nSum += PrintArrayBwrd3(a, m);
	return nSum + a[m];
}


int PrintArrayBwrd4(int a[], int n)		// n/3��, 1��, n/3��, 1��, n/3��
{
	/***
	[����]    [0,n-1] --> [0,m1-1] m1 [m1+1,m2-1] m2 [m2+1,n-1]
	[�Ϲݱ�Ģ] p(a,n) ::= m1=n/3,m2=n*2/3,
						s=p(a+m2+1,n-m2-1), a[m2] ���,
						s+=p(a+m1+1,m2-m1-1), a[m1] ���,
						s+=p(a,m1),
						s+a[m1]+a[m2] ��ȯ
	[�������] n�� 1/3�� ���� --> �����뼱: n==2
	[�ߴ�����] p(a,2) ::= m1=0,m2=1,
						s=p(a+2,0), a[1] ���,
						s+=p(a+1,0), a[0] ���,
						s+=p(a,0),
						s+a[0]+a[1] ��ȯ			--> n==0, p(a,0) ?
	[�ܼ���]   n==1: a[0] ���, a[0] ��ȯ
			  n==0: ��� x, ��ȯ 0
	***/
	int nSum = 0;
	if (n <= 1) {
		if (n == 1) {
			printf("%d ", a[0]);
			nSum += a[0];
		}
		return nSum;
	}
	int m1 = n / 3, m2 = n * 2 / 3;
	nSum += PrintArrayBwrd4(a + m2 + 1, n - m2 - 1);
	printf("%d ", a[m2]);
	nSum += PrintArrayBwrd4(a + m1 + 1, m2 - m1 - 1);
	printf("%d ", a[m1]);
	nSum += PrintArrayBwrd4(a, m1);
	return nSum + a[m1] + a[m2];
}

int PrintArrayBwrd5(int a[], int n)		// n/4��, 1��, n/4��, 1��, n/4��, 1��, n/4��
{
	/***
	[����]    [0,n-1] --> [0,m1-1] m1 [m1+1,m2-1] m2 [m2+1,m3-1] m3 [m3+1,n-1]
	[�Ϲݱ�Ģ] p(a,n) ::= m1=n/4,m2=n/2, m3=n*3/4,
						s=p(a+m3+1,n-m3-1), a[m3] ���,
						s+=p(a+m2+1,m3-m2-1), a[m2] ���,
						s+=p(a+m1+1,m2-m1-1), a[m1] ���,
						s+=p(a,m1),
						s+a[m1]+a[m2]+a[m3] ��ȯ
	[�������] n�� 1/4�� ���� --> �����뼱: n==3
	[�ߴ�����] p(a,3) ::= m1=0,m2=1,m3=2
						s=p(a+3,0), a[2] ���,
						s+=p(a+2,0), a[1] ���,
						s+=p(a+1,0), a[0] ���,
						s+=p(a,0),
						s+a[0]+a[1]+a[2] ��ȯ	--> n==0, p(a,0) ?
	[�ܼ���]   n==2: a[1] a[0] ���, a[1]+a[0] ��ȯ
			  n==1: a[0] ���, a[0] ��ȯ
			  n==0: ��� x, ��ȯ 0
	***/
	int nSum = 0;
	if (n <= 2) {
		switch (n) {
		case 2:
			printf("%d ", a[1]);
			nSum += a[1];
		case 1:
			printf("%d ", a[0]);
			nSum += a[0];
		}
		return nSum;
	}
	int m1 = n / 4, m2 = n / 2, m3 = n * 3 / 4;
	nSum += PrintArrayBwrd5(a + m3 + 1, n - m3 - 1);
	printf("%d ", a[m3]);
	nSum += PrintArrayBwrd5(a + m2 + 1, m3 - m2 - 1);
	printf("%d ", a[m2]);
	nSum += PrintArrayBwrd5(a + m1 + 1, m2 - m1 - 1);
	printf("%d ", a[m1]);
	nSum += PrintArrayBwrd5(a, m1);
	return nSum + a[m1] + a[m2] + a[m3];
}