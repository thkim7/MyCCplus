#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

//#define DEBUGGING

void main()
{
	NodePtr Add(NodePtr pList, int nData);
	NodePtr Insert(NodePtr pList, int nData, NodePtr pPrev);
	NodePtr Delete(NodePtr pList, int nData);
	NodePtr Find(NodePtr pList, int nData);
	void Reverse(NodePtr pList);
	void PrintList(NodePtr pList);
	void PutcharList(NodePtr pList);
	NodePtr pList = NULL;
	NodePtr pPrev = NULL;
	const char* sCmnd[] = {
		"a 200",
		"i 100",
		"f 200",
		"i 400",
		"i 300",
		"r",
		"i 400",
		"i 300",
		"d 300",
		"d 400",
		"d 100",
		"d 200",
		"a 193",
		"a 105",
		"a 185",
		"r",
		"f 100",
		"i 225",
		"f 185",
		"i 233",
		"i 181",
		"i 186",
		"f 225",
		"i 184",
		"i 177",
		"f 105",
		"i 32",
		"i 115",
		"f 193",
		"i 32",
		"i 182",
		"a 183",
		"a 218",
		"a 192",
		"e"
	};
	int nNdx = -1;
	while (1) {
		const char* pCmnd = sCmnd[++nNdx];
#ifdef DEBUGGING
		printf("? %s\n", pCmnd);
#endif
		if (*pCmnd == 'e')
			break;
		int nData = atoi(pCmnd + 1);
		switch (*pCmnd) {
		case 'a':
			pList = Add(pList, nData);
			break;
		case 'f':
			pPrev = Find(pList, nData);
			break;
		case 'i':
			pList = Insert(pList, nData, pPrev);
			break;
		case 'd':
			pList = Delete(pList, nData);
			break;
		case 'r':
			Reverse(pList);
		}
#ifdef DEBUGGING
		PrintList(pList);
#endif
	}
	PutcharList(pList);
	printf("Bye, ...\n\n");
}

NodePtr Add(NodePtr pList, int nData)
{	// pList가 가리키는 연결 리스트의 제일 앞에 nData를 가지는 노드를 삽입한다.
	NodePtr pNew = new Node;
	if (pNew) {
		pNew->nData = nData;
		pNew->link = pList;
		pList = pNew;
	}
	return pList;
}

NodePtr Find(NodePtr pList, int nData)
{	// 노드의 데이타 값이 nData 값을 가지는 첫 번째 노드를 찾아(없으면 NULL) return한다.
	NodePtr ptr = pList;
	while (ptr) {
		if (ptr->nData == nData)
			break;
		ptr = ptr->link;
	}
	return ptr;
}

NodePtr Insert(NodePtr pList, int nData, NodePtr pPrev)
{	// pList가 가리키는 연결 리스트에서 pPrev 노드 뒤에 nData를 가지는 노드를 삽입한다.
	// 만약 pPrev가 NULL이면 제일 앞에 삽입한다.
	NodePtr pNew = new Node;
	if (pNew) {
		pNew->nData = nData;
		if (pPrev) {
			pNew->link = pPrev->link;
			pPrev->link = pNew;
		}
		else {
			pNew->link = pList;
			pList = pNew;
		}
	}
	return pList;
}

NodePtr Delete(NodePtr pList, int nData)
{	// 노드의 데이타 값이 nData 값을 가지는 모든 노드를 삭제한다.
	// 노드를 삭제하기 위하여 이전 노드를 알아야 하는데,
	// 별도의 변수 pTrail를 만들어 바로 뒤에 따라 오도록 하여
	// pTrail이 현재의 노드의 이전 노드가 되도록 한다.
	NodePtr pTrail = NULL;
	NodePtr ptr = pList;
	while (ptr) {
		if (ptr->nData == nData) {
			NodePtr pDel = ptr;
			ptr = ptr->link;
			if (pTrail)
				pTrail->link = ptr;
			else
				pList = ptr;
			delete pDel;
		}
		else {
			pTrail = ptr;
			ptr = ptr->link;
		}
	}
	return pList;
}

void Reverse(NodePtr pList)
{	// 리스트의 데이터 값을 거꾸로 뒤집는데 아래와 같이 한다.
	// pList를 한 노드씩 따라가면서 노드의 nData를 스택에 push하고
	// pList를 한 노드씩 따라가면서 노드의 nData에 pop하여 저장한다.
	StackPtr pStack = NULL;
	NodePtr ptr = pList;
	while (ptr) {
		Push(pStack, ptr->nData);
		ptr = ptr->link;
	}
	ptr = pList;
	while (ptr) {
		ptr->nData = Pop(pStack);
		ptr = ptr->link;
	}
}

void PrintList(NodePtr pList)
{
	while (pList) {
		printf("%d ", pList->nData);
		pList = pList->link;
	}
	printf("\n\n");
}

void PutcharList(NodePtr pList)
{	// pList를 한 노드씩 따라가면서 노드의 nData를 putchar를 사용하여 출력한다.
	while (pList) {
		putchar(pList->nData);
		pList = pList->link;
	}
	printf("\n\n");
}