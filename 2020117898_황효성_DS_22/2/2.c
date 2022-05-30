#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE 100

typedef struct queueType {
	int data[MAX_SIZE];
	int front;
	int rear;
}queueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(queueType* q)
{
	q->front = -1;
	q->rear = -1;

	int i;
	for (i = 0;i < MAX_SIZE;i++)
	{
		q->data[i] = 0;
	}
}

int is_queue_empty(queueType* q)
{
	return q->front == q->rear;
}

int is_queue_full(queueType* q)
{
	return q->rear == MAX_SIZE - 1;
}

void enqueue(queueType* q, int data)
{
	if (is_queue_full(q))
	{
		error("queue is full");
	}
	else
	{
		q->data[++q->rear] = data;
	}
}

int dequeue(queueType* q)
{
	if (is_queue_empty(q))
	{
		error("queue is empty");
	}
	

	return q->data[++(q->front)];

}

void display_queue(queueType q[])
{
	int i,j;
	printf("Queue의 내용 ---\n");
	for (i = 0;i < 10;i++)
	{
		printf("%5d", i);
	}
	printf("\n");

	for (i = 3;i >=0;i--)
	{
		for (j = 0;j < 10;j++)
		{
			if (q[j].data[i] ==0)
			{
				printf("     ");
			}
			else
			{
				printf("%5d", q[j].data[i]);
			}
		}
		printf("\n\n");
	}
	printf("--------------------------------------------------\n");
}

void display(int* list, int n)
{
	int i;
	for (i = 0;i < n;i++)
	{
		printf("%5d", list[i]);
	}
	printf("\n\n");
}

void radix_sort(int* list, int d, int n)
{
	queueType queue[10];

	int i, b, j;
	int factor = 1;

	for (b = 0;b < 10;b++) {
		init_queue(&queue[b]);
	}

	for (j = 0;j < d;j++)
	{
		printf("step %d 자리 ---\n\n", j);
		for (b = 0;b < 10;b++) 
		{
			init_queue(&queue[b]);
		}

		for (i = 0;i < n;i++)
		{
			enqueue(&queue[(list[i] / factor) % 10], list[i]);
		}

		for (b = i = 0;b < 10;b++)
		{
			while (!is_queue_empty(&queue[b]))
			{
				list[i++] = dequeue(&queue[b]);
			}


		}

		display_queue(queue);
		display(list, n);

		factor *= 10;
	}

}


int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");

	int i;
	int d, n;
	int data;
	int list[MAX_SIZE];

	fscanf(fa,"%d %d", &d, &n);

	printf("input data ---\n");

	for (i = 0;i < n;i++)
	{
		fscanf(fa, "%d", &data);
		printf("  %3d", data);
		list[i] = data;
	}
	printf("\n\n");


	radix_sort(list, d, n);

	printf("result ---\n");
	display(list, n);

	return 0;
}