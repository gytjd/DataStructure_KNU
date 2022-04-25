#include <stdio.h>

typedef struct treeNode {
	char data;
	struct treeNode* llink;
	struct treeNode* rlink;
}treeNode;

treeNode a1 = { 'D',NULL,NULL };
treeNode a2 = { 'E',NULL,NULL };
treeNode a3 = { 'B',&a1,&a2 };
treeNode a4 = { 'C',NULL,NULL };
treeNode a5 = { 'A',&a3,&a4 };
treeNode* root = &a5;

void my_inorder(treeNode* root)
{
	if (root)
	{
		my_inorder(root->llink);
		printf("%p: %p %c %p\n", &(*root), root->llink, root->data, root->rlink);
		my_inorder(root->rlink);
	}
}

void my_preorder(treeNode* root)
{
	if (root)
	{
		printf("%p: %p %c %p\n", &(*root), root->llink, root->data, root->rlink);
		my_inorder(root->llink);
		my_inorder(root->rlink);
	}
}

void my_postorder(treeNode* root)
{
	if (root)
	{
		my_inorder(root->llink);
		my_inorder(root->rlink);
		printf("%p: %p %c %p\n", &(*root), root->llink, root->data, root->rlink);

	}
}

int main()
{
	printf("creating a binary tree\n\n");

	printf("three binary tree traversals\n");
	printf("inorder traversal\n");
	my_inorder(root);


	printf("\npreorder traversal : \n");
	my_preorder(root);

	printf("\npostorder traversal : \n");
	my_postorder(root);

	return 0;
}