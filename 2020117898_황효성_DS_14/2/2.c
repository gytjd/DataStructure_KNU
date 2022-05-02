#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE 1
#define FALSE 0

typedef struct threadedTree *threadedPointer;
typedef struct threadedTree {

    char data;
    threadedPointer leftChild;
    threadedPointer rightChild;
    short int rightThread;
    short int leftThread;
}threadedTree;

threadedTree a9 = { 'I',NULL,NULL,0,0};
threadedTree a8 = { 'H',NULL,NULL,0,0 };
threadedTree a7 = { 'G',NULL,NULL,0,0 };
threadedTree a6 = { 'F',NULL,NULL,0,0 };
threadedTree a5 = { 'E',NULL,NULL,0,0 };
threadedTree a4 = { 'D',NULL,NULL,0,0 };
threadedTree a3 = { 'C',NULL,NULL,0,0 };
threadedTree a2 = { 'B',NULL,NULL,0,0 };
threadedTree a1 = { 'A',NULL,NULL,0,0 };
threadedTree header = { '-',&a1,&header,0,0 };
threadedPointer root = &header;

threadedPointer insucc(threadedPointer tree)
{
    threadedPointer temp;
    temp = tree->rightChild;

    if (!tree->rightThread)
    {
        while (!temp->leftThread)
        {
            temp = temp->leftChild;
        }
    }

    return temp;
}

void tinorder(threadedPointer tree)
{
    threadedPointer temp = tree;
    printf("%p(%d, %p, %c, %d, %p)\n", &(*temp), temp->leftThread, temp->leftChild, temp->data, temp->rightThread, temp->rightChild);
    while (1)
    {
        temp = insucc(temp);

        if (temp == tree)
        {
            break;
        }
        printf("%p(%d, %p, %c, %d, %p)\n", &(*temp), temp->leftThread, temp->leftChild, temp->data, temp->rightThread, temp->rightChild);
    }
}

void insertRight(threadedPointer s,threadedPointer r)
{
    threadedPointer temp;
    
    r->rightChild=s->rightChild;
    r->rightThread=s->rightThread;
    
    r->leftChild=s;
    r->leftThread=TRUE;
    
    s->rightChild=r;
    s->rightThread=FALSE;
    
    if(!r->rightThread)
    {
        temp=insucc(r);
        temp->leftChild=r;
    }
}

void insertLeft(threadedPointer s,threadedPointer r)
{
    threadedPointer temp;
    
    r->leftChild=s->leftChild;
    r->leftThread=s->leftThread;
    
    r->rightChild=s;
    r->rightThread=TRUE;
    
    s->leftChild=r;
    s->leftThread=FALSE;
    
    if(!r->leftThread)
    {
        temp=insucc(r);
        temp->rightChild=r;
    }
}

void inorder_my(threadedPointer tree)
{
    if(tree)
    {
        inorder_my(tree->leftChild);
        printf("%c",tree->data);
        inorder_my(tree->rightChild);
    }
}

int main()
{
    a1.rightChild=&header;
    a1.rightThread=TRUE;
    a1.leftChild=&header;
    a1.leftThread=TRUE;
    
    insertLeft(&a1, &a2);
    insertRight(&a1, &a3);
    
    insertLeft(&a2, &a4);
    insertRight(&a2, &a5);
    
    insertLeft(&a3, &a6);
    insertRight(&a3, &a7);
    
    insertLeft(&a4, &a8);
    insertRight(&a4, &a9);
    
    tinorder(root);

    return 0;
}


