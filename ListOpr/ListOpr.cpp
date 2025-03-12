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
{	// pList�� ����Ű�� ���� ����Ʈ�� ���� �տ� nData�� ������ ��带 �����Ѵ�.
	NodePtr pNew = new Node;
	if (pNew) {
		pNew->nData = nData;
		pNew->link = pList;
		pList = pNew;
	}
	return pList;
}

NodePtr Find(NodePtr pList, int nData)
{	// ����� ����Ÿ ���� nData ���� ������ ù ��° ��带 ã��(������ NULL) return�Ѵ�.
	NodePtr ptr = pList;
	while (ptr) {
		if (ptr->nData == nData)
			break;
		ptr = ptr->link;
	}
	return ptr;
}

NodePtr Insert(NodePtr pList, int nData, NodePtr pPrev)
{	// pList�� ����Ű�� ���� ����Ʈ���� pPrev ��� �ڿ� nData�� ������ ��带 �����Ѵ�.
	// ���� pPrev�� NULL�̸� ���� �տ� �����Ѵ�.
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
{	// ����� ����Ÿ ���� nData ���� ������ ��� ��带 �����Ѵ�.
	// ��带 �����ϱ� ���Ͽ� ���� ��带 �˾ƾ� �ϴµ�,
	// ������ ���� pTrail�� ����� �ٷ� �ڿ� ���� ������ �Ͽ�
	// pTrail�� ������ ����� ���� ��尡 �ǵ��� �Ѵ�.
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
{	// ����Ʈ�� ������ ���� �Ųٷ� �����µ� �Ʒ��� ���� �Ѵ�.
	// pList�� �� ��徿 ���󰡸鼭 ����� nData�� ���ÿ� push�ϰ�
	// pList�� �� ��徿 ���󰡸鼭 ����� nData�� pop�Ͽ� �����Ѵ�.
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
{	// pList�� �� ��徿 ���󰡸鼭 ����� nData�� putchar�� ����Ͽ� ����Ѵ�.
	while (pList) {
		putchar(pList->nData);
		pList = pList->link;
	}
	printf("\n\n");
}