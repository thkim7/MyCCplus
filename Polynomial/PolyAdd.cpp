#include <stdio.h>

#define MAX_TERM 100
#pragma warning (disable: 4326 4805 4996 6031)

typedef int Polynomial[2 * (MAX_TERM + 1)];	/* Polynomial: ���׽��� �����Ѵ� */

void main()
{
	Polynomial polyA = { 3, 6, 3, -1, 2, -2, 1, };					// ���� ����, (���, ����)
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
			if (InputPolynomial(polyA, "A") == 0)					// ���׽� A�� �Է��Ѵ�.
				printf("Input Error\n");
			break;
		case 2:
			if (InputPolynomial(polyB, "B") == 0)					// ���׽� B�� �Է��Ѵ�.
				printf("Input Error\n");
			break;
		case 3:
			if (AddPolynomial(polyA, polyB, polyC))					// ���Ѵ�.
				OutputPolynomial(polyC, "C(X) = ");					// C�� ����Ѵ�.
			break;
		case 4:
			if (SubPolynomial(polyA, polyB, polyC))					// ����.
				OutputPolynomial(polyC, "C(X) = ");					// C�� ����Ѵ�.
			break;
		case 5:
			SimpleMulPolynomial(polyA, polyB[1], polyB[2], polyC);	// �� ���� ���Ѵ�.
			OutputPolynomial(polyC, "C(X) = ");						// C�� ����Ѵ�.
			SimpleMulPolynomial(polyB, polyA[1], polyA[2], polyC);	// �� ���� ���Ѵ�.
			OutputPolynomial(polyC, "C(X) = ");						// C�� ����Ѵ�.
			break;
		case 6:
			if (MultiplyPolynomial(polyA, polyB, polyC))			// ���Ѵ�.
				OutputPolynomial(polyC, "C(X) = ");					// C�� ����Ѵ�.
			break;
		case 7:
			OutputPolynomial(polyA, "A(X) = ");						// A�� ����Ѵ�.
			OutputPolynomial(polyB, "B(X) = ");						// B�� ����Ѵ�.
			break;
		default:
			bContinue = false;
		}
		putchar('\n');
	}
	printf("Bye, ....\n\n");
}

int Attach(Polynomial aPoly, int nCoef, int nExpon)
{	// ������ ������ �ִ��� �����Ͽ� �� ���� ���� �����ϰ� T/F�� ��ȯ�Ѵ�.
	if (aPoly[0] >= MAX_TERM)
		return false;
	int nNdx = ++aPoly[0] * 2 - 1;
	aPoly[nNdx] = nCoef;
	aPoly[nNdx + 1] = nExpon;
	return true;
}

int AddPolynomial(Polynomial A, Polynomial B, Polynomial C)
{	// �� ���׽� A, B�� ���Ͽ� ���׽� C�� �����ϰ� T/F�� ��ȯ�Ѵ�.
	C[0] = 0;		// ���׽� �ʱ�ȭ
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
{	// ���׽� A���� ���׽� B�� ���� ���׽� C�� �����ϰ� T/F�� ��ȯ�Ѵ�.
	C[0] = 0;		// ���׽� �ʱ�ȭ
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
{	// ���׽� A�� �� ���� ���Ͽ� ���׽� B�� �����Ѵ�.
	B[0] = 0;
	for (int i = 1, nLastA = A[0] * 2; i < nLastA; i += 2)
		Attach(B, A[i] * nCoef, A[i + 1] + nExpon);
}

int MultiplyPolynomial(Polynomial A, Polynomial B, Polynomial C)
{	// �� ���׽� A, B�� ���Ͽ� ���׽� C�� �����ϰ� T/F�� ��ȯ�Ѵ�.
	if (A[0] == 0)
		return (C[0] = 0) == 0;							// �� ���׽����� �ʱ�ȭ �� true ��ȯ
	int nLastA = A[0] * 2 - 1;
	int nCoef = A[nLastA];								// A�� ������ ���� ���
	int nExpon = A[nLastA + 1];							// A�� ������ ���� ����
	A[0]--;												// A�� ������ ���� �и��Ѵ�
	Polynomial C1, C2;									// �߰� ��� ���׽�
	SimpleMulPolynomial(B, nCoef, nExpon, C1);			// A�� ������ �װ� B�� ���Ѵ�
	int isOK = MultiplyPolynomial(A, B, C2) == true &&	// A�� �������� B�� ���Ѵ�
		AddPolynomial(C1, C2, C) == true;				// ���� �� ����� ���Ѵ�
	A[0]++;												// ���� ���׽����� �����Ѵ�
	return isOK;
}

int CheckPolynomial(Polynomial aPoly)
{	// ���׽��� �ùٸ��� üũ
	int bRight = true;
	int nLastNdx = aPoly[0] * 2;
	int nExpon, nPrvExpon = aPoly[2] + 1;
	for (int i = 1; i < nLastNdx; i += 2) {
		if (aPoly[i] == 0) {							// ����� 0���� ����
			fprintf(stderr, "%d ��° ���� ����� 0 �Դϴ�.\n", i);
			bRight = false;
		}
		nExpon = aPoly[i + 1];
		if (nExpon < 0 || nExpon >= nPrvExpon) {		// ������ ����̸鼭 ��������
			fprintf(stderr, "%d ��° ���� ������ �߸� �Ǿ����ϴ�.\n", i + 1);
			bRight = false;
		}
		nPrvExpon = nExpon;
	}
	return bRight;
}

int InputPolynomial(Polynomial aPoly, const char *szMsg)
{	// ���׽��� �Է�
	int nCtr;
	fprintf(stderr, "%s ���׽��� �Է��մϴ�.\n", szMsg);
	do {
		fprintf(stderr, "���� ������ ? ");
		scanf("%d", &nCtr);
	} while (nCtr < 0);
	if (nCtr > MAX_TERM) {
		fprintf(stderr, "���� �ʹ� �����ϴ�.\n");
		return false;
	}
	aPoly[0] = nCtr;									// ���� ������ ���
	nCtr *= 2;
	for (int i = 1; i < nCtr; i += 2) {
		fprintf(stderr, "%d ��° ���� ����� ? ", i / 2 + 1);
		scanf("%d", &aPoly[i]);
		fprintf(stderr, "%d ��° ���� ������ ? ", i / 2 + 1);
		scanf("%d", &aPoly[i + 1]);
	}
	return CheckPolynomial(aPoly);
}

void OutputPolynomial(Polynomial aPoly, const char *szMsg)
{	// ���׽��� ���
	printf(szMsg);
	if (aPoly[0] == 0)
		putchar('0');
	else {
		int nLastNdx = aPoly[0] * 2;
		for (int i = 1; i < nLastNdx; i += 2) {
			int nCoeff = aPoly[i];							// ���
			int nExpon = aPoly[i + 1];						// ����
			char cSign = '+';
			if (nCoeff < 0) {								// +/- �غ�
				cSign = '-';
				nCoeff = - nCoeff;
			}
			if (i != 1 || cSign == '-') { 					// ù ���� ����� ��츸 ����
				if (i == 1 && cSign == '-')					// ù ���� ����
					printf("-");
				else
					printf(" %c ", cSign);					// ��ȣ ���
			}
			if (nCoeff != 1 || nExpon == 0)
				printf("%d", nCoeff);						// ��� ���
			if (nExpon > 0) {
				putchar('X');
				if (nExpon > 1)
					printf("^%d", nExpon);					// ���� ���
			}
		}
	}
	putchar('\n');
}

