#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  MALLOC(p,s)\
   if(!((p) = malloc(s))){\
   fprintf(stderr,"Insufficient memory");\
   exit(EXIT_FAILURE);\
}
#define  MAX_NAME_SIZE  100
#define  MAX_LINE_SIZE  100

typedef struct {
    int id;
    char name[MAX_NAME_SIZE];
} element;

element* queue = NULL;
int front, rear;
int capacity = 2;

void qprint()
{
    int i = (front + 1) % capacity;

    do
    {
        printf("%d, %s\n", queue[i].id, queue[i].name);
        i = (i + 1) % capacity;
    } while (i != rear);
    printf("%d, %s\n\n", queue[i].id, queue[i].name);
    return;
}

void copy(element* a, element* b, element* c)
{
    while (a != b)
        *c++ = *a++;
}

void queueFull()
{
    int start;
    element* newQueue;
    MALLOC(newQueue, 2 * capacity * sizeof(*queue));

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

    printf("queue capacity is doubled,\n");
    printf("current queue capacity is %d.\n", capacity);
}

void quit()
{
    fprintf(stderr, "Queue empty");
    exit(EXIT_FAILURE);
}

void init()
{
    rear = 0;
    front = 0;
}

int is_empty()
{
    return (front == rear);
}

void add(element item)
{
    rear = (rear + 1) % capacity;
    if (front == rear) {
        queueFull();
        queue[++rear] = item;
        qprint();
    }
    else queue[rear] = item;
}

element delete()
{
    if (is_empty())
    {
        quit();
    }
    return queue[front++];
}

int main(void)
{
    MALLOC(queue, capacity * sizeof(*queue));
    FILE* fp;
    element student;
    char line[MAX_LINE_SIZE];
    char* context;
    char* delimiter = " \n";
    char* op = NULL;

    init(queue);
    printf("<<  circular queue operations using dynamic allocated array, where the initial capacity is 2  >>\n");
    printf("add 1 Jung\n");
    printf("delete\n\n");
    printf("**************************************************\n");

    if (fopen_s(&fp, "input.txt", "r"))
        exit(EXIT_FAILURE);

    while (1)
    {
        if (!(fgets(line, MAX_LINE_SIZE, fp)))
            break;
        op = strtok_s(line, delimiter, &context);

        if (!(strcmp(op, "add")))
        {
            sscanf_s(context, "%d %s", &student.id, student.name, (unsigned int)sizeof(student.name));
            add(student);
        }
        else if (!(strcmp(op, "delete")))
        {
            delete(queue);
        }
        else if (!(strcmp(op, "qprint")))
        {
            qprint(queue);
        }
        else if (!(strcmp(op, "quit")))
        {
            printf("end of program!!\n");
            break;
        }
        else
            printf("wrong command! try again!\n");
    }
    return 0;
}