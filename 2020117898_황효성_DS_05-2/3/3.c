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
int front = 0;
int rear = 0;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

int is_queue_empty()
{
	return front == rear;
}

int is_queue_full()
{
	return (((rear + 1) % MAX_QUEUE_SIZE) == front);
}

void qprint(element queue[])
{
	int i = front;
	do {
		i = (i + 1) % MAX_QUEUE_SIZE;

		printf("%d %s\n", queue[i].id, queue[i].name);
	} while (i != rear);

	printf("\n\n\n");
}
void add(element queue[], element student)
{
	if (is_queue_full())
	{
		printf("queue is full, not added\n");
		return;
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	queue[rear].id = student.id;
	strcpy(queue[rear].name, student.name);
}

element delete(element queue[])
{
	if (is_queue_empty())
	{
		error("queue is empty");
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
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