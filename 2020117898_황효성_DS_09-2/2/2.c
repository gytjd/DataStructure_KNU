#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  MALLOC(p,s)\
   if(!((p) = malloc(s))){\
   fprintf(stderr,"Insufficient memory");\
   exit(EXIT_FAILURE);\
}

#define MAX_LINE_SIZE 100
#define MAX_STACK_SIZE 3


typedef struct {
    int num;
    int class;
    int grade;
}element;

typedef struct QueueNode {
    element data;
    struct QueueNode* link;
}QueueNode;

typedef struct QueueType {
    QueueNode* front;
    QueueNode* rear;
}QueueType;
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(QueueType* q)
{
    q->front = NULL;
    q->rear = NULL;
}

int is_queue_empty(QueueType* q)
{
    return (q->front == NULL) && (q->rear == NULL);
}

void display_queue(QueueType* q)
{
    QueueNode* p = q->front;
    while (p != NULL)
    {
        printf("       %d     %d    %d\n", p->data.num, p->data.class, p->data.grade);
        p = p->link;
    }
}
void enqueue(QueueType* q, element data)
{
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    new_node->data = data;
    new_node->link = NULL;

    if (is_queue_empty(q))
    {
        q->front = new_node;
        q->rear = new_node;
    }
    else
    {
        q->rear->link = new_node;
        q->rear = new_node;
    }
}


int main(void)
{
    FILE* fp;
    char line[MAX_LINE_SIZE];
    char* delimiter = " \n";
    char* op = NULL;

    element student;
    QueueType class[3];
    init_queue(&class[0]);
    init_queue(&class[1]);
    init_queue(&class[2]);

    fp = fopen("input.txt", "r");


    while (1)
    {
        if (!(fgets(line, MAX_LINE_SIZE, fp)))
            break;

        fscanf(fp, "%d %d %d", &student.num, &student.class, &student.grade);
        enqueue(&class[student.num], student);
    }
    printf("과목번호, 학반, 성적\n");
    printf("**********************\n");
    display_queue(&class[0]);
    printf("**********************\n");
    display_queue(&class[1]);
    printf("**********************\n");
    display_queue(&class[2]);


    return 0;
}