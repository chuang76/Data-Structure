// for different tree traversals
/* 
	      1
	   2     3
	4    5
*/
 
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
}node;

// helper function
node* newNode(int data)
{
	node* ptr = (node *)malloc(sizeof(node));
	ptr->data = data;
	ptr->left = NULL;
	ptr->right = NULL;
	
	return ptr;
}

void printPreorder(node *);
void printInorder(node *);
void printPostorder(node *);

int main(void)
{
	node* root = newNode(1);		// return node
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);
	
	printf("Preorder traversal of binary tree is ");
	printPreorder(root);
	
	printf("\nInorder traversal of binary tree is ");
	printInorder(root);
	
	printf("\nPostorder traversal of binary tree is ");
	printPostorder(root);
	
	printf("\n");
	system("pause");
	return 0;
}

void printPreorder(node* ptr)		// ®Ú¥ª¥k 
{
	if(ptr == NULL)
		return;
	
	printf("%d ", ptr->data);
	printPreorder(ptr->left);
	printPreorder(ptr->right);
}

void printInorder(node* ptr)		// ¥ª®Ú¥k 
{
	if(ptr == NULL)
		return;
	
	printInorder(ptr->left);
	printf("%d ", ptr->data);
	printInorder(ptr->right);
}

void printPostorder(node* ptr)		// ¥ª¥k®Ú 
{
	if(ptr == NULL)
		return;
	
	printPostorder(ptr->left);
	printPostorder(ptr->right);
	printf("%d ", ptr->data);
}

