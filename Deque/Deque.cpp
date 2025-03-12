#include <stdio.h>
#pragma warning (disable: 4326 4996 6031)

#define N 10

typedef int Item;

typedef struct {
	Item items[N];
	int nFront;
	int nRear;
}	Queue, *QueuePtr;

void main()
{
	int  IsEmptyQueue(QueuePtr pQueue);
	int  IsFullQueue(QueuePtr pQueue);
	int  AddQueue(QueuePtr pQueue, Item nItem);
	int  JumpInQueue(QueuePtr pQueue, Item nItem);
	int  DeleteQueue(QueuePtr pQueue, Item& nItem);
	int  YieldQueue(QueuePtr pQueue, Item& nItem);
	void PrintQueue(QueuePtr pQueue);
	int  Error(const char *sMsg);

	/** Create Queue **/
	Queue aQueue;
	aQueue.nFront = aQueue.nRear = 0;
	while (1) {
		int value;
		printf("-3:끝, -2:양보, -1:삭제, 0~999:삽입, *:새치기 ? ");
		scanf("%d", &value);
		if (value < -2)
			break;
		else if (value == -2) {
			if (YieldQueue(&aQueue, value) == false)
				Error("empty");
			else
				printf("%d is deleted(양보)\n", value);
		}
		else if (value == -1) {
			if (DeleteQueue(&aQueue, value) == false)
				Error("empty");
			else
				printf("%d is deleted(삭제)\n", value);
		}
		else if (value < 1000) {
			if (AddQueue(&aQueue, value) == false)
				Error("full");
			else
				printf("%d is inserted(삽입)\n", value);
		}
		else {
			if (JumpInQueue(&aQueue, value %= 1000) == false)
				Error("full");
			else
				printf("%d is inserted(새치기)\n", value);
		}
		PrintQueue(&aQueue);
	}
}

int IsEmptyQueue(QueuePtr pQueue)
{	// 큐가 비었는지에 따라 T/F를 반환한다.
	return pQueue->nFront == pQueue->nRear;
}

int IsFullQueue(QueuePtr pQueue)
{	// 큐가 가득 찼는지에 따라 T/F를 반환한다.
	return (pQueue->nRear + 1) % N == pQueue->nFront;
}

int AddQueue(QueuePtr pQueue, Item nItem)
{	// 큐에 nItem을 추가하는데 승패에 따라 T/F를 반환한다.
	if (IsFullQueue(pQueue))
		return false;
	pQueue->items[pQueue->nRear = (pQueue->nRear + 1) % N] = nItem;	// rear를 증가하여 넣음
	return true;
}

int JumpInQueue(QueuePtr pQueue, Item nItem)
{	// 큐에 nItem을 앞끝에 새치기하는데 승패에 따라 T/F를 반환한다.
	if (IsFullQueue(pQueue))
		return false;
	pQueue->items[pQueue->nFront] = nItem;
	pQueue->nFront = (pQueue->nFront + N - 1) % N;	// front에 item을 넣고 감소
	return true;
}

int DeleteQueue(QueuePtr pQueue, Item& nItem)
{	// 큐에서 삭제하여 nItem에 저장하는데 승패에 따라 T/F를 반환한다.
	if (IsEmptyQueue(pQueue))
		return false;
	nItem = pQueue->items[pQueue->nFront = (pQueue->nFront + 1) % N];	// front를 증가하여 받아냄
	return true;
}

int YieldQueue(QueuePtr pQueue, Item& nItem)
{	// 큐에서 뒤끝을 삭제하여 nItem에 저장하는데 승패에 따라 T/F를 반환한다.
	if (IsEmptyQueue(pQueue))
		return false;
	nItem = pQueue->items[pQueue->nRear];
	pQueue->nRear = (pQueue->nRear + N - 1) % N;	// rear의 item을 받아내고 감소
	return true;
}

void PrintQueue(QueuePtr pQueue)
{
	int nCtr = (pQueue->nRear - pQueue->nFront + N) % N;
	for (int i = 1; i <= nCtr; i++)
		printf("--%d-", (pQueue->nFront + i) % N);
	printf("--\n");
	for (int i = 1; i <= nCtr; i++)
		printf("%3d ", pQueue->items[(pQueue->nFront + i) % N]);
	printf("\n");
	for (int i = 1; i <= nCtr; i++)
		printf("----");
	printf("--\n\n");
}

int Error(const char *sMsg)
{
	printf("***** Queue is %s. *****\n", sMsg);
	return -1;
}
