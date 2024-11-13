/* 
 * �ۼ���:2021-12-09
 * ��  ��: 20210054 
 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STRING 20

 // ť ��� ����ü NODE ����
typedef struct node
{
	char data;
	struct node *next;
} NODE;

// ť ��� ����ü QUEUE ����
typedef struct
{
	int count;
	NODE *front;
	NODE *rear;
} QUEUE;

void printQueue(QUEUE *q);
int enqueue(QUEUE *q, char data);
int dequeue(QUEUE *q, char *data);
int isEmpty(QUEUE *q);

int main()
{
	int len, i, ioRes;
	char str[MAX_STRING];
	QUEUE queue; // ť

	// ť �ʱ�ȭ
	queue.count = 0;
	queue.front = NULL;
	queue.rear = NULL;



	while (1)
	{
		printf(">> ");
		ioRes = scanf("%s", str);

		if (ioRes == EOF)
			break;

		len = strlen(str);
		for (i = 0; i < len; i++)
		{
			enqueue(&queue, str[i]);// enqueue �Լ� ȣ��
		}

		printQueue(&queue);

	} // while

	printf("bye!\n");

	return 0;
} // main

void printQueue(QUEUE *q)
{
	char data;

	printf("   ");
	while (dequeue(q, &data)) // ť�� �� ������ dequeue �Լ� ȣ��
	{
		printf("%c", data);
	}
	printf("\n\n");
} // printQueue

// enqueue ������ 1, ���н� 0
int enqueue(QUEUE *q, char data)
{
	NODE *temp;

	// ť ��� ����
	temp = (NODE*)malloc(sizeof(NODE));
	if (!temp) // ���� �Ҵ� ���н�
		return 0;

	// ������ ��忡 �� ����
	temp->data = data;
	temp->next = NULL;

	if (isEmpty(q))// ť�� ��� �ִ� ���(isEmpty �Լ� ȣ��)
	{
		q->front = temp;
		q->rear = temp;

	}
	else
	{
		q->rear->next = temp;
		q->rear = temp;

	}
	q->count++;
	return 1;
} // enqueue

// dequeue ������ 1, ���н� 0
int dequeue(QUEUE *q, char *data)
{
	NODE *temp;

	if (isEmpty(q)) // ť�� ��� �ִ� ���
		return 0;

	*data = q->front->data;
	temp = q->front;
	if (q->front == q->rear) {
		q->rear = NULL;
	}
	q->front = temp->next;
	free(temp);


	q->count--;
	return 1;
} // dequeue

// ť�� ��� ������ 1, �׷��� ������ 0�� ��ȯ
int isEmpty(QUEUE *q)
{
	return q->rear == NULL;
}