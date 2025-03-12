#pragma warning (disable: 4326 4996 6054)

typedef int Item;

typedef struct node {
	int nData;
	struct node* link;
}	Node, * NodePtr, * StackPtr;

int  IsEmptyStack(StackPtr pStack);
int  Push(StackPtr& pStack, Item nItem);
Item Pop(StackPtr& pStack);
