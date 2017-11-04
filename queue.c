
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

void initQueue(QUEUE * Q);
void enQueue(QUEUE * Q, p_datatype value);
bool isemptyQueue(QUEUE * Q);
bool is_fullQueue(QUEUE * Q);
void deQueue(QUEUE * Q, p_datatype value);
void traverseQueue(QUEUE * Q);

/***************************************** 主函数测试入口 ********************************************/
int main(void)
{
	datatype val;
	QUEUE queue;
	initQueue(&queue);
	int i;
	for(i=1;i<10;i++)
	{
		memcpy(val.buf,"test",5);
		enQueue(&queue, &val);
	}
	enQueue(&queue, &val);
	enQueue(&queue, &val);
	enQueue(&queue, &val);
	enQueue(&queue, &val);
	enQueue(&queue, &val);
	enQueue(&queue, &val);

	traverseQueue(&queue);
	deQueue(&queue, &val);
	deQueue(&queue, &val);

	traverseQueue(&queue);
	enQueue(&queue, &val);
	enQueue(&queue, &val);
	enQueue(&queue, &val);
	deQueue(&queue, &val);
	deQueue(&queue, &val);
	deQueue(&queue, &val);
	deQueue(&queue, &val);
	deQueue(&queue, &val);
	deQueue(&queue, &val);
	deQueue(&queue, &val);
	deQueue(&queue, &val);
	traverseQueue(&queue);

	return 0;
}


/**************************************初始化一个空的循环队列 ******************************************/
void initQueue(QUEUE * Q)
{
	Q->QBase = (p_datatype)calloc(Queue_Size,sizeof(datatype));
	if(Q->QBase == NULL)
	{
		printf("内存分配失败！\n");
		exit(-1);
	}

	Q->front = Q->rear = 0;
}


/***************插入一个新元素  注：插入前需要先判断该队列是否已满，避免覆盖有效数据******************/
void enQueue(QUEUE * Q, p_datatype value)
{

	if(is_fullQueue(Q))
	{
		printf("循环队列已满，拒绝插入%s！\n", value->buf);
	}
	else
	{
		memcpy(Q->QBase[Q->rear].buf, value->buf,sizeof(value->buf));
		Q->rear = (Q->rear + 1) % Queue_Size;
		printf("\n %s 入队 \n", value->buf);
	}
}


/**************  删除一个元素,并通过指针返回该数  注:删除前要判断该队列是否为空。*******
	************/
void deQueue(QUEUE * Q, p_datatype value)
{
	if(isemptyQueue(Q))
	{
		printf("循环队列已空！");
	}
	else
	{
		*value = Q->QBase[Q->front];
		memcpy(value->buf,Q->QBase[Q->front].buf,sizeof(Q->QBase[Q->front].buf));
	printf("\n %s 出队 \n", value->buf);
		Q->front = (Q->front + 1) % Queue_Size;
	}
}


/************************************	  判断循环队列是否为空 ************************************/
bool isemptyQueue(QUEUE * Q)
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
bool is_fullQueue(QUEUE * Q)
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
	if(isemptyQueue(Q))
	{
		printf("循环队列为空!\n");
		return;
	}

	printf("当前循环队列 :\n");
	printf("front是%d,rear是%d :\n", Q->front, Q->rear);

	int tail = Q->front;

	while(tail != Q->rear)
	{
		printf(" %s ", Q->QBase[tail].buf);
		tail = (tail + 1) % Queue_Size;
	}
}


