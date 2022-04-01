#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

element queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

int is_queue_empty()
{
	return (front == rear);
}

int is_queue_full()
{
	return (rear == MAX_QUEUE_SIZE-1);
}

void qprint(element queue[])
{
	if (is_queue_empty())
	{
		error("queue is empty,cannot delete element");
	}
	int i;
	for (i = front+1;i <= rear;i++)
	{
		printf("%d %s\n", queue[i].id, queue[i].name);
	}
	printf("\n\n\n");
}

void data_shift1(element queue[])
{
	element temp;
	temp = queue[0];
	queue[0] = queue[1];
	queue[1] = temp;

	temp = queue[1];
	queue[1] = queue[2];
	queue[2] = temp;

	front = -1;
	rear = 1;
	printf("data shift\n");
}

void data_shift2(element queue[])
{
	element temp;
	temp = queue[0];
	queue[0] = queue[2];
	queue[2]=temp;
	front = -1;
	rear = 0;
	printf("data shift\n");
}
void add(element queue[], element student)
{
	int i=0;
	if (is_queue_full())
	{
		if (front == 0)
		{
			data_shift1(queue);
			rear += 1;
			queue[rear].id = student.id;
			strcpy(queue[rear].name, student.name);
			return;
		}
		if (front == 1)
		{
			data_shift2(queue);
			rear += 1;
			queue[rear].id = student.id;
			strcpy(queue[rear].name, student.name);
			return;
		}
		printf("queue is full,not added\n");
		return;
	}

	rear += 1;
	queue[rear].id = student.id;
	strcpy(queue[rear].name, student.name);
}

element delete(element queue[])
{
	if (is_queue_empty())
	{
		error("queue is empty, cannot delete element");
	}
	return queue[++front];

}

int main()
{
	FILE* fpa;

	char* delimiter = " \n";
	char* context;
	char* op = NULL;

	element student;
	char line[MAX_NAME_SIZE];

	printf("<< Circular queue operations where MAX_QUEUE_SIZE is 3 >>\n");
	printf("add 1 Jung\n");
	printf("delete\n");
	printf("\n***************************************\n");

	if (fopen_s(&fpa, "input.txt", "r"))
		exit(1);

	while (1)
	{
		if (!(fgets(line, MAX_NAME_SIZE, fpa)))
			break;

		op = strtok_s(line, delimiter, &context);

		if (!strcmp(op, "add"))
		{
			sscanf_s(context, "%d %s", &student.id, student.name, (unsigned int)sizeof(student.name));
			add(queue, student);
		}
		else if (!strcmp(op, "delete"))
		{
			delete(queue);
		}
		else if (!strcmp(op, "qprint"))
		{
			qprint(queue);
		}
		else if (!strcmp(op, "quit"))
		{
			break;
		}
		else
		{
			printf("wrong command! try again!\n");
		}
	}
	fclose(fpa);

	return 0;
}
