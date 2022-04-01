#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 20

#define MALLOC(p,s)\
if(!((p) = malloc(s))) {\
fprintf(stderr,"insufficient memory");\
exit(EXIT_FAILURE);\
}

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

element* queue;

int capacity = 2;
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
	return (((rear + 1) % capacity) == front);
}

void qprint(element queue[])
{
	int i = front;
	do {
		i = (i + 1) % capacity;

		printf("%d %s\n", queue[i].id, queue[i].name);
	} while (i != rear);

	printf("\n\n\n");
}

void copy(element* a, element* b, element* c)
{
	while (a != b)
	{
		*c++ = *a++;
	}
}

void queueFull(element* queue)
{
	int start;

	element* newQueue;
	MALLOC(newQueue, 2 * capacity * sizeof(*queue));

	if (!newQueue) {
		fprintf(stderr, "Insufficient memory\n");
		exit(EXIT_FAILURE);
	}

	start = (front + 1) % capacity;

	if (start < 2)
	{
		copy(queue + start, queue + start + capacity - 1, newQueue);
	}
	else
	{
		copy(queue + start, queue + capacity, newQueue);
		copy(queue, queue + rear + 1, newQueue + capacity - start);
	}

	front = 2 * capacity - 1;
	rear = capacity - 2;
	capacity *= 2;

	free(queue);
	queue = newQueue;
}

void add(element queue[], element student)
{
	rear = (rear + 1) % capacity;
	if (front == rear)
	{
		queueFull(queue);
		queue[++rear] = student;
	}
	else

	{
		queue[rear] = student;
	}
}

element delete(element queue[])
{
	if (is_queue_empty())
	{
		error("queue is empty");
	}
	front = (front + 1) % capacity;
	return queue[front];
}
int main()
{
	queue = (element*)malloc(sizeof(*queue) * 2);

	FILE* fpa;

	char* delimiter = " \n";
	char* context;
	char* op = NULL;

	element student;
	char line[MAX_NAME_SIZE];

	printf("<< Circular queue operations using dynamic allocated array,whre the initial capacity is 2>>\n");
	printf("add 1 Jung\n");
	printf("delete\n");
	printf("\n***************************************\n");

	if (fopen_s(&fpa, "input.txt", "r"))
	{
		exit(1);
	}

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
	free(queue);

	return 0;
}