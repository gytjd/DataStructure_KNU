#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 8
#define MAX_NAME_SIZE 30

typedef struct {
	int id;
	int price;
	char name[MAX_NAME_SIZE];
}element;

element queue[MAX_QUEUE_SIZE];
int front1;
int rear1;

int front2;
int rear2;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue()
{
	front1 = 0;
	rear1 = 0;

	front2 = 4;
	rear2 = 4;
}

int is_firstQueue_empty()
{
	return front1 == rear1;
}

int is_secondQueue_empty()
{
	return front2 == rear2;
}

int is_firstQueue_full()
{
	return ((rear1 + 1) % (MAX_QUEUE_SIZE / 2))==front1;
}

int is_secondQueue_full()
{
	int temp;
	if ((rear2 + 1) % MAX_QUEUE_SIZE == 0)
	{
		temp = 4;

		if (temp == front2)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return ((rear2 + 1) % MAX_QUEUE_SIZE) == front2;
	}
}

void push_1(element data)
{
	if (is_firstQueue_full())
	{
		printf("1 번 queue is full, not added\n\n");
		return;
	}

	rear1 = (rear1 + 1) % (MAX_QUEUE_SIZE / 2);
	queue[rear1] = data;
}

element pop_1()
{
	if (is_firstQueue_empty())
	{
		printf("1 번 queue is empty\n\n");
		return;
	}

	front1 = (front1 + 1) % (MAX_QUEUE_SIZE / 2);

	return queue[front1];
}

void push_2(element data)
{
	if (is_secondQueue_full())
	{
		printf("2 번 queue is full,not added\n\n");
		return;
	}
	else
	{

		rear2 = (rear2 + 1) % MAX_QUEUE_SIZE;
		if (rear2 == 0)
		{
			rear2 = 4;
		}
		queue[rear2] = data;
	}
}

element pop_2()
{
	if (is_secondQueue_empty())
	{
		printf("2 번 queue is empty, cannot delete element\n\n");
		return;
	}
	else
	{
		front2 = (front2 + 1) % MAX_QUEUE_SIZE;

		if (front2 == 0)
		{
			front2 = 4;
		}
	}

	return queue[front2];
}

void display_1()
{
	int i = front1;

	printf("1번 queue : front = %d, rear = %d\n", front1, rear1);

	do {
		i = (i + 1) % (MAX_QUEUE_SIZE / 2);

		printf("%d %s\n", queue[i].price, queue[i].name);
	} while (i != rear1);
	printf("\n\n");
}

void display_2()
{
	int i = front2;

	printf("2번 queue : front = %d, rear = %d\n", front2, rear2);

	do {
		i = (i + 1) % MAX_QUEUE_SIZE;

		if (i == 0)
		{
			i = 4;
		}

		printf("%d %s\n", queue[i].price, queue[i].name);
	} while (i != rear2);
	printf("\n\n");
}
int main()
{
	FILE* fa;
	fa = fopen("input2.txt", "r");

	char* op;
	char* delimiter = " \n";
	char* context;

	int num;
	char line[MAX_NAME_SIZE];
	element data;

	init_queue();
	while (1)
	{
		if (!fgets(line, MAX_NAME_SIZE, fa))
			break;

		op = strtok_s(line, delimiter, &context);

		if (strcmp(op, "add") == 0)
		{
			sscanf(context, "%d %d %s", &data.id, &data.price, &data.name);

			if (data.id == 1)
			{
				push_1(data);
			}
			else
			{
				push_2(data);
			}
		}
		else if (strcmp(op, "delete") == 0)
		{
			sscanf(context, "%d", &num);
			if (num == 1)
			{
				pop_1();
			}
			else
			{
				pop_2();
			}
		}
		else if (strcmp(op, "qprint") == 0)
		{
			sscanf(context, "%d", &num);

			if (num == 1)
			{
				display_1();
			}
			else
			{
				display_2();
			}
		}
		else if (strcmp(op, "quit") == 0)
		{
			break;
		}
		else
		{
			printf("Wrong Command! try again!\n");
		}
	}
}