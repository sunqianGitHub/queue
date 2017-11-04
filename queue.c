
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
	false,
	true
}bool;
typedef struct{
	char buf[256];
}datatype,*p_datatype;
/*******************************************************************************************************************
定义循环队列的结构体。注：循环队列是在数组的基础上实现的，所以需要一个指向首元素的指针，另外头和尾用int来表示相对偏移量即可。 
********************************************************************************************************************/
typedef struct Queue
{
p_datatype		QBase;
int 			front;
int 			rear;
} QUEUE;


#define Queue_Size				5

void InitQueue(QUEUE * Q);
void EnQueue(QUEUE * Q, p_datatype value);
bool isEmptyQueue(QUEUE * Q);
bool isFullQueue(QUEUE * Q);
void DeQueue(QUEUE * Q, p_datatype value);
void traverseQueue(QUEUE * Q);

/***************************************** 主函数测试入口 ********************************************/
int main(void)
{
	datatype val;
	QUEUE queue;
	InitQueue(&queue);
	int i;
	for(i=1;i<10;i++)
	{
		memcpy(val.buf,"test",5);
		EnQueue(&queue, &val);
	}
	EnQueue(&queue, &val);
	EnQueue(&queue, &val);
	EnQueue(&queue, &val);
	EnQueue(&queue, &val);
	EnQueue(&queue, &val);
	EnQueue(&queue, &val);

	traverseQueue(&queue);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);

	traverseQueue(&queue);
	EnQueue(&queue, &val);
	EnQueue(&queue, &val);
	EnQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	traverseQueue(&queue);

	return 0;
}


/**************************************初始化一个空的循环队列 ******************************************/
void InitQueue(QUEUE * Q)
{
	Q->QBase = (p_datatype)calloc(Queue_Size,sizeof(datatype));
	if(Q->QBase == NULL)
	{
		printf("calloc ERROR\n");
		exit(-1);
	}

	Q->front = Q->rear = 0;
}


/***************插入一个新元素  注：插入前需要先判断该队列是否已满，避免覆盖有效数据******************/
void EnQueue(QUEUE * Q, p_datatype value)
{

	if(isFullQueue(Q))
	{
		printf("EnQueue ERROR，cant insert %s\n", value->buf);
	}
	else
	{
		memcpy(Q->QBase[Q->rear].buf, value->buf,sizeof(value->buf));
		Q->rear = (Q->rear + 1) % Queue_Size;
		printf(" %s insert \n", value->buf);
	}
}


/**************  删除一个元素,并通过指针返回该数  注:删除前要判断该队列是否为空。*******
	************/
void DeQueue(QUEUE * Q, p_datatype value)
{
	if(isEmptyQueue(Q))
	{
		printf("EmptyQueue\n");
	}
	else
	{
		memcpy(value->buf,Q->QBase[Q->front].buf,sizeof(Q->QBase[Q->front].buf));
		printf(" %s DeQueue \n", value->buf);
		Q->front = (Q->front + 1) % Queue_Size;
	}
}


/************************************	  判断循环队列是否为空 ************************************/
bool isEmptyQueue(QUEUE * Q)
{
	if(Q->front == Q->rear)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/************************************	 判断循环队列是否已满 ************************************/
bool isFullQueue(QUEUE * Q)
{
	if((Q->rear + 1) % Queue_Size == Q->front)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/*************************************	   遍历循环队列中的各元素 *************************************/
void traverseQueue(QUEUE * Q)
{
	if(isEmptyQueue(Q))
	{
		printf("循环队列为空!\n");
		printf("EmptyQueue\n");
		return;
	}

	printf("round-robin queue:\n");
	printf("front is %d,rear is %d :\n", Q->front, Q->rear);

	int tail = Q->front;

	while(tail != Q->rear)
	{
		printf(" %s \n", Q->QBase[tail].buf);
		tail = (tail + 1) % Queue_Size;
	}
}


