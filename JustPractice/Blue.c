//
//  Blue.c
//  KNU C
//
//  Created by hwang hyosung on 2022/04/06.
//

#define _CRT_SECURE_NO_WARNINGS

#include "Blue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode *listPointer;
typedef struct listNode {
    int data;
    listPointer link;
}listNode;

listPointer first;

void error(char *message)
{
    fprintf(stderr,"%s\n",message);
    exit(1);
}

void init_list()
{
    first=NULL;
}

void display_list(listPointer head)
{
    int count=0;
    listPointer p=head;
    
    while(p!=NULL)
    {
        if(count%10==0)
        {
            printf("\n");
        }
        printf("%d ",p->data);
        p=p->link;
        count++;
    }
    printf("\n");
}
void find(listPointer head,listPointer *x,int data)
{
    listPointer p=head;
    if(p==NULL) // empty list
    {
        *x=NULL;
    }
    else // non -empty list
    {
        if(p->data>data)
        {
            *x=NULL;
        }
        else
        {
            while(p!=NULL)
            {
                if(p->data<data)
                {
                    *x=p;
                    p=p->link;
                }
                else
                {
                    break;
                }
            }
        }
    }
}
void insert_node(listPointer *head,listPointer x,int data)
{
    listPointer new_node=(listPointer)malloc(sizeof(listPointer));
    new_node->data=data;
    new_node->link=NULL;
    
    if(*head==NULL)
    {
        (*head)=new_node;
    }
    else if(x==NULL)
    {
        new_node->link=(*head);
        (*head)=new_node;
    }
    else
    {
        new_node->link=x->link;
        x->link=new_node;
    }
}

void delete(listPointer *first,listPointer trail,listPointer x)
{
    if(trail)
    {
        trail->link=x->link;
    }
    else
    {
        *first=x->link;
    }
    free(x);
}

void delete_less50(listPointer *head)
{
    listPointer p=*head;
    listPointer removed=p;
    listPointer pre=NULL;
    
    while(p!=NULL)
    {
        if(p->data<=50)
        {
            removed=p;
            p=p->link;
            delete(head, pre, removed);
        }
        else
        {
            pre=p;
            p=p->link;
        }
    }
    
}
int main()
{
    FILE *fa;
    int data;
    listPointer x,trail;
    
    init_list();
    
    fa=fopen("input.txt", "r");
    while(fscanf(fa,"%d",&data)!=EOF)
    {
        find(first, &x, data);
        insert_node(&first, x, data);
    }
    
    printf("The ordered list contains : \n");
    display_list(first);
    
    printf("\n\nAfter deleting nodes with data less than and equal to 50 \n");
    printf("The ordered list contains : \n");;
    delete_less50(&first);
    display_list(first);
    
    return 0;
}

