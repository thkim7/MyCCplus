#include <stdio.h>

#define MAX_TERM 100
#pragma warning (disable: 4326 4805 4996 6031)

typedef int Polynomial[2 * (MAX_TERM + 1)];	/* Polynomial: 다항식을 정의한다 */

void main()
{
	Polynomial polyA = { 3, 6, 3, -1, 2, -2, 1, };					// 항의 개수, (계수, 지수)
	Polynomial polyB = { 4, 5, 4, -1, 2, 2, 1, 8, 0, };
	Polynomial polyC;
	int InputPolynomial(Polynomial A, const char *szMsg);
	void OutputPolynomial(Polynomial A, const char *szMsg);
	int CheckPolynomial(Polynomial A);
	int Attach(Polynomial aPoly, int nCoef, int nExpon);
	int AddPolynomial(Polynomial A, Polynomial B, Polynomial C);
	int SubPolynomial(Polynomial A, Polynomial B, Polynomial C);
	void SimpleMulPolynomial(Polynomial A, int nCoef, int nExpon, Polynomial B);
	int MultiplyPolynomial(Polynomial A, Polynomial B, Polynomial C);
	CheckPolynomial(polyA);
	CheckPolynomial(polyB);
	int bContinue = true;
	while (bContinue) {
		int nFtn;
		printf("1: A, 2: B, 3: Add, 4: Sub, 5: Simple, 6: Mul, 7: pr ? ");
		scanf("%d", &nFtn);
		switch (nFtn) {
		case 1:
			if (InputPolynomial(polyA, "A") == 0)					// 다항식 A를 입력한다.
				printf("Input Error\n");
			break;
		case 2:
			if (InputPolynomial(polyB, "B") == 0)					// 다항식 B를 입력한다.
				printf("Input Error\n");
			break;
		case 3:
			if (AddPolynomial(polyA, polyB, polyC))					// 더한다.
				OutputPolynomial(polyC, "C(X) = ");					// C를 출력한다.
			break;
		case 4:
			if (SubPolynomial(polyA, polyB, polyC))					// 뺀다.
				OutputPolynomial(polyC, "C(X) = ");					// C를 출력한다.
			break;
		case 5:
			SimpleMulPolynomial(polyA, polyB[1], polyB[2], polyC);	// 한 항을 곱한다.
			OutputPolynomial(polyC, "C(X) = ");						// C를 출력한다.
			SimpleMulPolynomial(polyB, polyA[1], polyA[2], polyC);	// 한 항을 곱한다.
			OutputPolynomial(polyC, "C(X) = ");						// C를 출력한다.
			break;
		case 6:
			if (MultiplyPolynomial(polyA, polyB, polyC))			// 곱한다.
				OutputPolynomial(polyC, "C(X) = ");					// C를 출력한다.
			break;
		case 7:
			OutputPolynomial(polyA, "A(X) = ");						// A를 출력한다.
			OutputPolynomial(polyB, "B(X) = ");						// B를 출력한다.
			break;
		default:
			bContinue = false;
		}
		putchar('\n');
	}
	printf("Bye, ....\n\n");
}

int Attach(Polynomial aPoly, int nCoef, int nExpon)
{	// 저장할 공간이 있는지 조사하여 한 항을 끝에 저장하고 T/F를 반환한다.
	if (aPoly[0] >= MAX_TERM)
		return false;
	int nNdx = ++aPoly[0] * 2 - 1;
	aPoly[nNdx] = nCoef;
	aPoly[nNdx + 1] = nExpon;
	return true;
}

int AddPolynomial(Polynomial A, Polynomial B, Polynomial C)
{	// 두 다항식 A, B를 더하여 다항식 C에 저장하고 T/F를 반환한다.
	C[0] = 0;		// 다항식 초기화
	int nNdxA = 1, nNdxB = 1, nLastA = A[0] * 2, nLastB = B[0] * 2;
	while (nNdxA < nLastA && nNdxB < nLastB) {
		if (A[nNdxA + 1] > B[nNdxB + 1]) {
			if (Attach(C, A[nNdxA], A[nNdxA + 1]) == false)
				return false;
			nNdxA += 2;
		}
		else if (A[nNdxA + 1] == B[nNdxB+ 1]) {
			int nCoeff = A[nNdxA] + B[nNdxB];
			if (nCoeff)
				if (Attach(C, nCoeff, A[nNdxA + 1]) == false)
					return false;
			nNdxA += 2;
			nNdxB += 2;
		}
		else {	// A Expon < B Expon
			if (Attach(C, B[nNdxB], B[nNdxB + 1]) == false)
				return false;
			nNdxB += 2;
		}
	}
	while (nNdxA < nLastA) {
		if (Attach(C, A[nNdxA], A[nNdxA + 1]) == false)
			return false;
		nNdxA += 2;
	}
	while (nNdxB < nLastB) {
		if (Attach(C, B[nNdxB], B[nNdxB + 1]) == false)
			return false;
		nNdxB++;
	}
	return true;
}

int SubPolynomial(Polynomial A, Polynomial B, Polynomial C)
{	// 다항식 A에서 다항식 B를 빼서 다항식 C에 저장하고 T/F를 반환한다.
	C[0] = 0;		// 다항식 초기화
	int nNdxA = 1, nNdxB = 1, nLastA = A[0] * 2, nLastB = B[0] * 2;
	while (nNdxA < nLastA && nNdxB < nLastB) {
		if (A[nNdxA + 1] > B[nNdxB + 1]) {
			if (Attach(C, A[nNdxA], A[nNdxA + 1]) == false)
				return false;
			nNdxA += 2;
		}
		else if (A[nNdxA + 1] == B[nNdxB+ 1]) {
			int nCoeff = A[nNdxA] - B[nNdxB];
			if (nCoeff)
				if (Attach(C, nCoeff, A[nNdxA + 1]) == false)
					return false;
			nNdxA += 2;
			nNdxB += 2;
		}
		else {	// A Expon < B Expon
			if (Attach(C, -B[nNdxB], B[nNdxB + 1]) == false)
				return false;
			nNdxB += 2;
		}
	}
	while (nNdxA < nLastA) {
		if (Attach(C, A[nNdxA], A[nNdxA + 1]) == false)
			return false;
		nNdxA += 2;
	}
	while (nNdxB < nLastB) {
		if (Attach(C, -B[nNdxB], B[nNdxB + 1]) == false)
			return false;
		nNdxB++;
	}
	return true;
}

void SimpleMulPolynomial(Polynomial A, int nCoef, int nExpon, Polynomial B)
{	// 다항식 A와 한 항을 곱하여 다항식 B에 저장한다.
	B[0] = 0;
	for (int i = 1, nLastA = A[0] * 2; i < nLastA; i += 2)
		Attach(B, A[i] * nCoef, A[i + 1] + nExpon);
}

int MultiplyPolynomial(Polynomial A, Polynomial B, Polynomial C)
{	// 두 다항식 A, B를 곱하여 다항식 C에 저장하고 T/F를 반환한다.
	if (A[0] == 0)
		return (C[0] = 0) == 0;							// 빈 다항식으로 초기화 후 true 반환
	int nLastA = A[0] * 2 - 1;
	int nCoef = A[nLastA];								// A의 마지막 항의 계수
	int nExpon = A[nLastA + 1];							// A의 마지막 항의 지수
	A[0]--;												// A의 마지막 항을 분리한다
	Polynomial C1, C2;									// 중간 결과 다항식
	SimpleMulPolynomial(B, nCoef, nExpon, C1);			// A의 마지막 항과 B를 곱한다
	int isOK = MultiplyPolynomial(A, B, C2) == true &&	// A의 나머지와 B를 곱한다
		AddPolynomial(C1, C2, C) == true;				// 위의 두 결과를 더한다
	A[0]++;												// 원래 다항식으로 복원한다
	return isOK;
}

int CheckPolynomial(Polynomial aPoly)
{	// 다항식이 올바른지 체크
	int bRight = true;
	int nLastNdx = aPoly[0] * 2;
	int nExpon, nPrvExpon = aPoly[2] + 1;
	for (int i = 1; i < nLastNdx; i += 2) {
		if (aPoly[i] == 0) {							// 계수가 0인지 조사
			fprintf(stderr, "%d 번째 항의 계수가 0 입니다.\n", i);
			bRight = false;
		}
		nExpon = aPoly[i + 1];
		if (nExpon < 0 || nExpon >= nPrvExpon) {		// 지수가 양수이면서 내림차순
			fprintf(stderr, "%d 번째 항의 지수가 잘못 되었습니다.\n", i + 1);
			bRight = false;
		}
		nPrvExpon = nExpon;
	}
	return bRight;
}

int InputPolynomial(Polynomial aPoly, const char *szMsg)
{	// 다항식을 입력
	int nCtr;
	fprintf(stderr, "%s 다항식을 입력합니다.\n", szMsg);
	do {
		fprintf(stderr, "항의 갯수는 ? ");
		scanf("%d", &nCtr);
	} while (nCtr < 0);
	if (nCtr > MAX_TERM) {
		fprintf(stderr, "항이 너무 많습니다.\n");
		return false;
	}
	aPoly[0] = nCtr;									// 항의 갯수를 기록
	nCtr *= 2;
	for (int i = 1; i < nCtr; i += 2) {
		fprintf(stderr, "%d 번째 항의 계수는 ? ", i / 2 + 1);
		scanf("%d", &aPoly[i]);
		fprintf(stderr, "%d 번째 항의 지수는 ? ", i / 2 + 1);
		scanf("%d", &aPoly[i + 1]);
	}
	return CheckPolynomial(aPoly);
}

void OutputPolynomial(Polynomial aPoly, const char *szMsg)
{	// 다항식을 출력
	printf(szMsg);
	if (aPoly[0] == 0)
		putchar('0');
	else {
		int nLastNdx = aPoly[0] * 2;
		for (int i = 1; i < nLastNdx; i += 2) {
			int nCoeff = aPoly[i];							// 계수
			int nExpon = aPoly[i + 1];						// 지수
			char cSign = '+';
			if (nCoeff < 0) {								// +/- 준비
				cSign = '-';
				nCoeff = - nCoeff;
			}
			if (i != 1 || cSign == '-') { 					// 첫 항이 양수일 경우만 제외
				if (i == 1 && cSign == '-')					// 첫 항이 음수
					printf("-");
				else
					printf(" %c ", cSign);					// 부호 출력
			}
			if (nCoeff != 1 || nExpon == 0)
				printf("%d", nCoeff);						// 계수 출력
			if (nExpon > 0) {
				putchar('X');
				if (nExpon > 1)
					printf("^%d", nExpon);					// 지수 출력
			}
		}
	}
	putchar('\n');
}

