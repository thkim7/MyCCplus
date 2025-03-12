#include <stdio.h>
#include "Node.h"

// �̹� ���������� ������ ���� ����Ʈ�� �����Ѵ�.
// push�� ù ���� �����ϰ�, pop�� ù ��带 ���������ν� �����ȴ�.

int IsEmptyStack(StackPtr pStack)
{
	return pStack == NULL;
}

int Push(StackPtr& pStack, Item nItem)
{	// nItem�� ù ���� ���������ν� ���ÿ� nItem�� push�ϴµ� ���п� ���� T/F�� ��ȯ�Ѵ�.
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
{	// ù ��带 ���������ν� ���ÿ��� pop�Ͽ� nItem(�����ϸ� -1)�� ��ȯ�Ѵ�.
	Item nItem = -1;
	if (pStack) {
		NodePtr pDel = pStack;
		nItem = pDel->nData;
		pStack = pDel->link;
		delete pDel;
	}
	return nItem;
}