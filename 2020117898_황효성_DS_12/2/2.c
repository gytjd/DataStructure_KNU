#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100



typedef struct treeNode {
	char data;
	struct treeNode* llink;
	struct treeNode* rlink;
}treeNode;

treeNode *queue[MAX_QUEUE_SIZE];
treeNode* ptr = NULL;

int front = -1;
int rear = -1;

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
	return rear == MAX_QUEUE_SIZE - 1;
}


void enqueue(char data)
{
	if (is_queue_full())
	{
		error("큐가 가득차있습니다.");
	}
	else
	{
		treeNode* new_node = (treeNode*)malloc(sizeof(treeNode));

		new_node->data = data;
		new_node->llink = NULL;
		new_node->rlink = NULL;

		queue[++rear] = new_node;
	}
}

char dequeue()
{
	if (is_queue_empty())
	{
		error("큐가 비어있습니다.");
	}
	else
	{
		queue[++front];
	}
}

void insert_node()
{
	int i;
	for (i = 0;i < 9;i++)
	{
		if (ptr == NULL)
		{
			ptr = queue[++front];
		}
		else
		{
			if (queue[front]->llink == NULL)
			{
				queue[front]->llink = queue[i];
			}
			else if (queue[front]->rlink == NULL)
			{
				queue[front]->rlink = queue[i];
				dequeue();
			}
		}
		
	}
	return;
}

void my_inorder(treeNode* root)
{
	if (root)
	{
		my_inorder(root->llink);
		printf("%c ", root->data);
		my_inorder(root->rlink);
	}
}

void my_preorder(treeNode* root)
{
	if (root)
	{
		printf("%c ", root->data);
		my_preorder(root->llink);
		my_preorder(root->rlink);
	}
}

void my_postorder(treeNode* root)
{
	if (root)
	{
		my_postorder(root->llink);
		my_postorder(root->rlink);
		printf("%c ", root->data);
	}
}
int main()
{
	FILE* fa;
	fa = fopen("input.txt", "r");


	int i;
	char data;

	for (i = 0;i < 9;i++)
	{
		fscanf(fa, "%c", &data);
		enqueue(data);
	}
	printf("creating a complete binary tree\n");
	insert_node();

	printf("\nthree binary tree traversals\n");

	printf("inorder traversal :");
	my_inorder(ptr);
	printf("\n");

	printf("preorder traversal :");
	my_preorder(ptr);
	printf("\n");

	printf("postorder traversal :");
	my_postorder(ptr);
	printf("\n");


	return 0;
}