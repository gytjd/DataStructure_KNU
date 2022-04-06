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
typedef struct StackNode {
    element data;
    struct Stacknode* link;
}StackNode;

typedef struct StackType {
    StackNode* top;
}StackType;

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_stack(StackType* s)
{
    s->top = NULL;
}

int is_stack_empty(StackType* s)
{
    return (s->top == NULL);
}

void display_stack(StackType* s)
{
    StackNode* p = s->top;

    while (p != NULL)
    {
        printf("       %d     %d    %d\n", p->data.num, p->data.class, p->data.grade);
        p = p->link;
    }
}

void push(StackType* s, element data)
{
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    new_node->data = data;
    new_node->link = NULL;

    if (is_stack_empty(s))
    {
        s->top = new_node;
    }
    else
    {
        new_node->link = s->top;
        s->top = new_node;
    }
}



int main(void)
{
    FILE* fp;
    char line[MAX_LINE_SIZE];
    char* delimiter = " \n";
    char* op = NULL;

    element student;
    StackType class[3];
    init_stack(&class[0]);
    init_stack(&class[1]);
    init_stack(&class[2]);

    fp = fopen("input.txt", "r");


    while (1)
    {
        if (!(fgets(line, MAX_LINE_SIZE, fp)))
            break;

        fscanf(fp, "%d %d %d", &student.num, &student.class, &student.grade);
        push(&class[student.num], student);
    }
    printf("과목번호, 학반, 성적\n");
    printf("**********************\n");
    display_stack(&class[0]);
    printf("**********************\n");
    display_stack(&class[1]);
    printf("**********************\n");
    display_stack(&class[2]);


    return 0;
}