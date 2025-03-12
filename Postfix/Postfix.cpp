#include <stdio.h>

#define STACK_SIZE 40
#define EXPR_SIZE  100
#define OPERANDS   5
#pragma warning(disable: 4326 4996 6031 6054)

typedef int Item;

typedef struct {
	int nTop;
	Item items[STACK_SIZE];
}	Stack, *StackPtr;

void main()
{
	void GetOperands(int nOprnd[]);
	int EvalPostfixExpr(char* sPostfixExpr, int* pnResult, int nOprnd[]);

	int nOprnd[] = {1, 2, 3, 4, 5};
	while (1) {
		char sPostfix[EXPR_SIZE];
		printf("Postfix Expr[?x] ? ");
		gets_s(sPostfix);
		int nResult;
		if (*sPostfix == 'x' || *sPostfix == NULL)
			return;
		else if (*sPostfix == '?')
			GetOperands(nOprnd);
		else {
			if (EvalPostfixExpr(sPostfix, &nResult, nOprnd - 'A'))
				printf("Result : %d\n", nResult);
			else
				printf(", Error\n");
		}
		putchar('\n');
	}
}

void GetOperands(int nOprnd[])						// 수식에 사용할 피연산자 값을 입력한다.
{
	for (int i = 0; i < OPERANDS; i++) {			// 피연산자 A부터 E까지
		int nVal;
		char values[20];
		printf("%c ? ", i + 'A');					// A부터 E사이의 피연산자
		gets_s(values);
		if (sscanf(values, "%d", &nVal) != 1)		// error가 나면 멈춘다.
			return;
		nOprnd[i] = nVal;							// 입력된 피연산자를 저장한다.
	}
}

int EvalPostfixExpr(char *sPostfixExpr, int *pnResult, int nOprnd[])
{
	int push(StackPtr pStack, Item nValue);
	int pop(StackPtr pStack, Item *pnValue);

	Stack aStack;
	aStack.nTop = -1;
	char *pToken = sPostfixExpr - 1;
	while (*++pToken) {
		if (*pToken >= 'A' && *pToken <= 'E') {
			if (push(&aStack, nOprnd[*pToken]) == false)
				return printf("Stack full") == 0;
		}
		else {
			int nValueA, nValueB;
			if (pop(&aStack, &nValueB) == false)
				return printf("Postfix") == 0;
			if (*pToken != '!' && *pToken != '#')
				if (pop(&aStack, &nValueA) == false)
					return printf("Postfix") == 0;
			switch (*pToken) {
			case '!':
				nValueA = (int)!nValueB;
				break;
			case '#':
				nValueA = nValueB + 1;
				break;
			case '*':
				nValueA *= nValueB;
				break;
			case '/':
				if (nValueB == 0)
					return printf("Divide by zero") == 0;
				nValueA /= nValueB;
				break;
			case '%':
				if (nValueB == 0)
					return printf("Divide by zero") == 0;
				nValueA %= nValueB;
				break;
			case '+':
				nValueA += nValueB;
				break;
			case '-':
				nValueA -= nValueB;
				break;
			case '<':
				nValueA = nValueA < nValueB;
				break;
			case '>':
				nValueA = nValueA > nValueB;
				break;
			case '=':
				nValueA = nValueA == nValueB;
				break;
			case '~':
				nValueA = nValueA != nValueB;
				break;
			case '&':
				nValueA = (int)(nValueA && nValueB);
				break;
			case '|':
				nValueA = (int)(nValueA || nValueB);
				break;
			default:
				return printf("No operator") == 0;
			}
			push(&aStack, nValueA);
		}
	}
	*pnResult = aStack.items[0];
	return aStack.nTop == 0 ? true : printf("Postfix") == 0;
}

int IsStackEmpty(StackPtr pStack)
{	// 스택이 비었는지를 return 한다
	return pStack->nTop < 0;
}

int IsStackFull(StackPtr pStack)
{	// 스택이 가득 찼는지를 return 한다
	return pStack->nTop >= STACK_SIZE - 1;
}

int push(StackPtr pStack, Item nValue)
{	// 스택에 nValue를 push하는데, true/false를 return 한다.
	if (IsStackFull(pStack))
		return false;
	pStack->items[++pStack->nTop] = nValue;
	return true;
}

int pop(StackPtr pStack, Item *pnValue)
{	// 스택에서 pop하여 pnValue에 저장하는데, true/false를 return 한다.
	if (IsStackEmpty(pStack))
		return false;
	*pnValue = pStack->items[pStack->nTop--];
	return true;
}
