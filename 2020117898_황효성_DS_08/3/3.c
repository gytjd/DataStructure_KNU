#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 30

typedef struct {
    char name[MAX_LEN];
    char from[MAX_LEN];
    char gender[MAX_LEN];
}element;
typedef struct listNode {
    element data;
    struct listNode* link;
}listNode;


void display(listNode* head)
{
    int count = 0;
    listNode* p = head;
    while (p != NULL)
    {
        if ((count % 2) == 0)
        {
            printf("\n");
        }
        printf("(%d, %s %s %s, %d)", &(*p), p->data.name, p->data.from, p->data.gender, p->link);
        p = p->link;
        count++;
    }
    printf("\n\n");
}


void insert_node(listNode** head, listNode* pre, element data)
{
    listNode* new_node = (listNode*)malloc(sizeof(listNode));
    new_node->data = data;
    new_node->link = NULL;

    if ((*head) == NULL)
    {
        *head = new_node;
    }
    else if (pre == NULL)
    {
        new_node->link = (*head);
        (*head) = new_node;
    }
    else
    {
        new_node->link = pre->link;
        pre->link = new_node;
    }
}

void insert_last(listNode** head, element data)
{
    listNode* new_node = (listNode*)malloc(sizeof(listNode));
    new_node->data = data;
    new_node->link = NULL;

    listNode* p = *head;

    if (p == NULL)
    {
        *head = new_node;
    }
    else
    {
        while (p->link != NULL)
        {
            p = p->link;
        }

        p->link = new_node;
    }
}

listNode* create_male(listNode* head)
{
    listNode* male = NULL;

    listNode* p = head;
    listNode* pre = NULL;

    while (p != NULL)
    {
        if (strcmp(p->data.gender, "남자") == 0)
        {
            insert_last(&male, p->data);
            pre = p;
        }

        p = p->link;
    }

    return male;
}

listNode* create_female(listNode* head)
{
    listNode* female = NULL;

    listNode* p = head;
    listNode* pre = NULL;

    while (p != NULL)
    {
        if (strcmp(p->data.gender, "여자") == 0)
        {
            insert_last(&female, p->data);
            pre = p;
        }

        p = p->link;
    }

    return female;
}
int main()
{
    FILE* fpa;

    char* delimiter = " \n";
    char* context;
    char* op = NULL;
    char line[MAX_LEN];

    int i;
    element student[6];
    listNode* head = NULL;
    listNode* male = NULL;
    listNode* female = NULL;


    fpa = fopen("input.txt", "r");

    for (i = 0; i < 6; i++)
    {
        fscanf(fpa, "%s %s %s", &student[i].name, &student[i].from, &student[i].gender);
    }
    for (i = 5; i >= 0; i--)
    {
        insert_node(&head, NULL, student[i]);
    }
    printf("전체 리스트\n");
    display(head);


    printf("남자 리스트\n");
    male = create_male(head);
    display(male);

    printf("여자리스트\n");
    female = create_female(head);
    display(female);

    fclose(fpa);
    return 0;
}


