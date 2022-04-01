#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMORY_SIZE 10
#define MAX_STACK 10

#define MAX_NAME_SIZE 100
#define MAX_LEN 100



typedef struct {
    int id;
    char name[MAX_NAME_SIZE];
}element;

element memory[MEMORY_SIZE];
int top[MAX_STACK];
int boundary[MAX_STACK];

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
/*
void stackFull(int i)
{
    fprintf(stderr,"Stack %d is Full",i);
    exit(EXIT_FAILURE);
}

int stackEmpty(int i)
{
    fprintf(stderr,"Stack %d is Empty",i);
    exit(EXIT_FAILURE);
}
*/
void push(int i, element item)
{
    if (top[i] == boundary[i + 1])
    {
        fprintf(stderr, "Stack %d is Full\n", i);
        return;
    }
    memory[top[i]++] = item;
    printf("%s is Pushed in Stack No. %d\n", item.name, item.id);
}


void pop(int i)
{
    if (top[i] == boundary[i])
    {
        printf("Stack %d is Empty\n", i);
        return;
    }
    printf("%s is popped from Stack No. %d\n", memory[--top[i]].name, i);

}

void sprint(int n)
{
    int i;
    printf("\n");
    for (i = boundary[n]; i < top[n]; i++)
    {
        printf("%s\n", memory[i].name);
    }
    printf("\n\n");
}

void sprint_total(element* s)
{
    int i, n = 0;
    while (n != 3)
    {
        printf("stack %d : \n", n);
        for (i = boundary[n]; i < top[n]; i++)
        {
            printf("%s\n", memory[i].name);
        }
        printf("\n\n");

        n++;
    }
}
int main()
{
    FILE* fpa;

    char* delimiter = " \n";
    char* context;
    char* op = NULL;

    element student;
    char line[MAX_LEN];
    int n, j;


    printf("How Many Stacks ? : ");
    scanf("%d", &n);


    printf("\n C Language program to implement the Multiple Stacks\n");
    printf("add stack_num(0-%d) name : add 0 kim\n", n - 1);
    printf("delete stack_num(0-%d) : delete 0\n", n - 1);
    printf("sprint stack_num(0-%d) : sprint 0\n", n - 1);
    printf("quit\n");
    printf("========================================================\n\n");

    top[0] = boundary[0] = 0;
    for (j = 1; j < n; j++)
    {
        top[j] = boundary[j] = (MEMORY_SIZE / n) * j;
    }
    boundary[n] = MEMORY_SIZE;


    fopen_s(&fpa,"input.txt", "r");

    while (1)
    {
        if (!(fgets(line, MAX_LEN, fpa)))
            break;

        op = strtok_s(line, delimiter, &context);

        if (!strcmp(op, "add"))
        {
            sscanf_s(context, "%d %s", &student.id, student.name, (unsigned int)sizeof(student.name));

            if (student.id >= 0 && student.id < n)
            {
                push(student.id, student);
            }
            else
            {
                printf("stack number error, try again\n");
            }
        }
        else if (!strcmp(op, "delete"))
        {
            sscanf_s(context, "%d %s", &student.id, student.name, (unsigned int)sizeof(student.name));
            pop(student.id);
        }
        else if (!strcmp(op, "sprint"))
        {

            sscanf_s(context, "%d %s", &student.id, student.name, (unsigned int)sizeof(student.name));

            if (student.id >= 0 && student.id < n)
            {
                sprint(student.id);
            }
            else
            {
                printf("stack number error, try again\n");
            }

        }
        else if (!strcmp(op, "quit"))
        {
            printf("\nProgram end\n\n");
            sprint_total(memory);
            {

            }
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


