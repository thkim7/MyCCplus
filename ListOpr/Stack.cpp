#include <stdio.h>
#include "Node.h"

// 이번 과제에서는 스택을 연결 리스트로 구현한다.
// push는 첫 노드로 삽입하고, pop은 첫 노드를 삭제함으로써 구현된다.

int IsEmptyStack(StackPtr pStack)
{
	return pStack == NULL;
}

int Push(StackPtr& pStack, Item nItem)
{	// nItem을 첫 노드로 삽입함으로써 스택에 nItem을 push하는데 승패에 따라 T/F를 반환한다.
	NodePtr pNew;
	pNew = new Node;
	if (pNew) {
		pNew->nData = nItem;
		pNew->link = pStack;
		pStack = pNew;
	}
	return pNew != NULL;
}

Item Pop(StackPtr& pStack)
{	// 첫 노드를 삭제함으로써 스택에서 pop하여 nItem(실패하면 -1)을 반환한다.
	Item nItem = -1;
	if (pStack) {
		NodePtr pDel = pStack;
		nItem = pDel->nData;
		pStack = pDel->link;
		delete pDel;
	}
	return nItem;
}