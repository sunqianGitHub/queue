
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
	false,
	true
}bool;
typedef unsigned int QueueRet;
#define ESUCCESS	0x7ff0	
#define EFAILED		0x7FF1

#define ENULL 	0x8ff1
#define EFULL	0x8ff2
#define EEMPTY	0x8ff3


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

QueueRet InitQueue(QUEUE * Q);
QueueRet EnQueue(QUEUE * Q, p_datatype value);
bool isEmptyQueue(QUEUE * Q);
bool isFullQueue(QUEUE * Q);
QueueRet DeQueue(QUEUE * Q, p_datatype value);
QueueRet traverseQueue(QUEUE * Q);
QueueRet Destroy_Queue(QUEUE * Q);

#define CHECK_POINTER(p1) \
	if(NULL == (p1)) \
    { \
        printf("Null Pointer: p1(%p)\n", p1); \
        return ENULL; \
    } 

/***************************************** 主函数测试入口 ********************************************/
int main(void)
{
	datatype val;
	QUEUE queue;
	InitQueue(&queue);
	sprintf(val.buf,"45");
	EnQueue(&queue, &val);
	sprintf(val.buf,"46");
	EnQueue(&queue, &val);
	sprintf(val.buf,"47");
	EnQueue(&queue, &val);
	sprintf(val.buf,"48");
	EnQueue(&queue, &val);
	sprintf(val.buf,"49");
	EnQueue(&queue, &val);
	EnQueue(&queue, &val);
	EnQueue(&queue, &val);

	traverseQueue(&queue);

	
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);

	traverseQueue(&queue);

	
	Destroy_Queue(&queue);
	
	sprintf(val.buf,"680000");
	EnQueue(&queue, &val);
	sprintf(val.buf,"690000");
	EnQueue(&queue, &val);
	sprintf(val.buf,"700000");
	EnQueue(&queue, &val);
	sprintf(val.buf,"710000");
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	DeQueue(&queue, &val);
	Destroy_Queue(&queue);
	traverseQueue(&queue);

	return 0;
}


/**************************************初始化一个空的循环队列 ******************************************/
QueueRet InitQueue(QUEUE * Q)
{
	Q->QBase = (p_datatype)calloc(Queue_Size,sizeof(datatype));
	if(NULL == Q->QBase)
	{
		printf("calloc ERROR\n");
		return EFAILED;
	}

	Q->front = Q->rear = 0;
	return ESUCCESS;
}


/***************插入一个新元素  注：插入前需要先判断该队列是否已满，避免覆盖有效数据******************/
QueueRet EnQueue(QUEUE * Q, p_datatype value)
{
	CHECK_POINTER(Q->QBase);

	if(isFullQueue(Q))
	{
		printf("EnQueue ERROR，cant insert %s\n", value->buf);
		return EFULL;
	}
	memcpy(Q->QBase[Q->rear].buf, value->buf,sizeof(value->buf));
	Q->rear = (Q->rear + 1) % Queue_Size;
	printf(" %s insert \n", value->buf);
	return ESUCCESS;
}


/**************  删除一个元素,并通过指针返回该数据:删除前要判断该队列是否为空。*******************/
QueueRet DeQueue(QUEUE * Q, p_datatype value)
{
	
	CHECK_POINTER(Q->QBase);
	if(isEmptyQueue(Q))
	{
		printf("EmptyQueue\n");
		return EEMPTY;
	}
	memcpy(value->buf,Q->QBase[Q->front].buf,sizeof(Q->QBase[Q->front].buf));
	printf(" %s DeQueue \n", value->buf);
	Q->front = (Q->front + 1) % Queue_Size;
	return ESUCCESS;
}


/************************************	  判断循环队列是否为空 ************************************/
QueueRet isEmptyQueue(QUEUE * Q)
{
	
	CHECK_POINTER(Q->QBase);
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
QueueRet isFullQueue(QUEUE * Q)
{
	
	CHECK_POINTER(Q->QBase);
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
QueueRet traverseQueue(QUEUE * Q)
{
	
	CHECK_POINTER(Q->QBase);
	if(isEmptyQueue(Q))
	{
		printf("EmptyQueue\n");
		return EEMPTY;
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
QueueRet Destroy_Queue(QUEUE * Q)
{
	
	CHECK_POINTER(Q->QBase);
	free(Q->QBase);
	Q->QBase = NULL;
	return ESUCCESS;
}

