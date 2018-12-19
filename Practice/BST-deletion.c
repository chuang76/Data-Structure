// BST deletion practice

#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int key;
	struct node *left, *right;
}node;

node* newNode(int key)		// utility function to create a new node
{
	node *n = malloc(sizeof(node));
	n->key = key;
	n->left = n->right = NULL;
	return n;
}

void inorder(node *n)		// left, root, right
{
	if(n != NULL)
	{
		inorder(n->left);
		printf("%d ", n->key);
		inorder(n->right);
	}
}

node* insert(node *n, int key)
{
	if(n == NULL)
		return newNode(key);			// �����طs��
	if(key < n->key)
		n->left = insert(n->left, key);
	else
		n->right = insert(n->right, key);
	return n; 
}

node* succ(node *n)		// �� successor �Y�O��̤p���k�l�� , �]�N�O�k�l��̥��䪺�`�I 
{
	node *tmp;
	for(tmp = n; tmp->left != NULL; tmp = tmp->left);
	return tmp;
}

node* deleteNode(node *n, int key)		// delete the given key and return new root
{
	node *tmp; 					// ���ӧR 
	if(n == NULL)
		return n;
	if(key < n->key)			// ������m , �� left child or right child ���n 
		n->left = deleteNode(n->left, key);		
	else if(key > n->key)
		n->right = deleteNode(n->right, key);
	else						// ���Ȥ@�ˤF , �i�H�}�l�R 
	{
		if(n->left == NULL)		// node with only one child or no child
		{
			tmp = n->right;
			free(n);
			return tmp;
		}
		else if(n->right == NULL)
		{
			tmp = n->left;
			free(n);
			return tmp;
		}
		else			// node with two children
		{
			tmp = succ(n->right);
			n->key = tmp->key;		// �Q successor ���N 
			n->right = deleteNode(n->right, tmp->key);		// ��쥻 successor �R��  
		}
	}
	return n; 
}
int main(void)
{
	node *root = NULL;
	root = insert(root, 50);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 70);
	root = insert(root, 20);
	root = insert(root, 80);
	root = insert(root, 60);
	
	printf("Inorder traversal of the given tree: ");
	inorder(root);
	
	printf("\nDelete 70\n");
	deleteNode(root, 70);
	printf("Inorder traversal of the modified tree: ");
	inorder(root);
	
	printf("\nDelete 20\n");
	deleteNode(root, 20);
	printf("Inorder traversal of the modified tree: ");
	inorder(root);
	
	printf("\nDelete 30\n");
	deleteNode(root, 30);
	printf("Inorder traversal of the modified tree: ");
	inorder(root);
	
	printf("\nDelete 50\n");
	deleteNode(root, 50);
	printf("Inorder traversal of the modified tree: ");
	inorder(root);
	
	printf("\nInsert 75\n");
	root = insert(root, 75);
	printf("Inorder traversal of the modified tree: ");
	inorder(root);
	printf("\n");
	
	return 0;
}

