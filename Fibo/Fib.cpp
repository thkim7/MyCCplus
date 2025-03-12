#include <stdio.h>

#pragma warning(disable: 4326 4996 6031)

void main()
{
	while (1) {
		int n;
		printf("n ? ");
		scanf("%d", &n);
		if (n < 0)
			break;
		int Fib(int);
		printf("Fib[%d] = %d\n\n", n, Fib(n));
	}

}

int Fib(int n)
{
	if (n <= 1)
		return n;
	return Fib(n - 1) + Fib(n - 2);
}
