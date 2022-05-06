#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 500

typedef struct node* nodePointer;
typedef struct node {
    int data;
    nodePointer leftChild;
    nodePointer rightChild;
}node;

nodePointer root = NULL;

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
nodePointer create_node(int data)
{
    nodePointer new_node = (nodePointer)malloc(sizeof(node));

    new_node->data = data;
    new_node->leftChild = NULL;
    new_node->rightChild = NULL;

    return new_node;
}

nodePointer insert_node(nodePointer root, int data)
{
    if (!root)
    {
        return create_node(data);
    }

    if ((root->data) > data)
    {
        root->leftChild = insert_node(root->leftChild, data);
    }
    else if ((root->data) < data)
    {
        root->rightChild = insert_node(root->rightChild, data);
    }
    return root;
}

void binary_search(nodePointer root, int data)
{
    if (root == NULL)
    {
        error("이진 탐색 트리가 비어있습니다.");
    }


    if (root->data > data)
    {
        printf("%d ==> ", root->data);
        binary_search(root->leftChild, data);
    }
    else if (root->data < data)
    {
        printf("%d ==> ", root->data);
        binary_search(root->rightChild, data);
    }
    else
    {
        printf("%d", data);
    }
}

void inorder_my(nodePointer root)
{
    if (root)
    {
        inorder_my(root->leftChild);
        printf("%d ", root->data);
        inorder_my(root->rightChild);
    }
}

int is_equal(int* key, int data, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (key[i] == data)
        {
            return 1;
        }
    }

    return 0;
}
int main()
{
    int i;
    int data;
    int n, seed;
    int find_num;

    int key[MAX_SIZE];


    printf("random number generation (1~ %d)\n", MAX_SIZE);
    printf("the number of nodes in BST (less than and equal to 50): ");
    scanf("%d", &n);

    printf("seed : ");
    scanf("%d", &seed);
    printf("\ncreating a BST from random numbers\n");

    srand(seed);

    printf("generating number : ");
    for (i = 0; i < n; i++)
    {
        data = (rand() % 500 + 1);

        if (is_equal(key, data, i) == 1)
        {
            i--;
            continue;
        }
        else
        {
            key[i] = data;
        }
        printf("%d ", data);
        root = insert_node(root, data);
    }

    printf("\n");

    printf("the key to search : ");
    scanf("%d", &find_num);
    printf("the search process : ");
    binary_search(root, find_num);
    printf("\nthe element is in BST\n\n");

    printf("inorder traversal of the BST shows the sorted sequence\n");
    inorder_my(root);
    printf("\n");

    return 0;

}


