// BST practice, include : insert, search, traversal, deletion
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int key;
	struct node *left, *right;
}node;

node* create(int);			// utility function, create a new node for a given key
void inorder(node*);
node* insert(node*, int);
node* search(node*, int);
void existed(node*, int);

int main(void)
{
	node *root = create(50);
	insert(root, 30);
	insert(root, 20);
	insert(root, 80);
	insert(root, 70);
	insert(root, 40);
	insert(root, 60);
	inorder(root);
	printf("\n");
	
	existed(root, 70);
	existed(root, 90);
	
	return 0;
}

node* create(int key)
{
	node *ptr = malloc(sizeof(node));
	ptr->key = key;
	ptr->left = NULL;
	ptr->right = NULL;
	return ptr;
}

void inorder(node *root)			// 中序走訪 
{
	if(root != NULL)
	{
		inorder(root->left);
		printf("%d ", root->key);
		inorder(root->right);
	}
}

node* insert(node* ptr, int key)		// 如果 insert key 重複的值會 ? 
{
	if(ptr == NULL)
		return create(key);
	if(key < ptr->key)
		ptr->left = insert(ptr->left, key);
	else if(key > ptr->key)
		ptr->right = insert(ptr->right, key);
	
	return ptr;			// return unchanged
}

node* search(node* ptr, int key)	
{
	if(ptr == NULL || ptr->key == key)		// ptr means current node
		return ptr;
	if(key < ptr->key)			// 往左邊找 
		return search(ptr->left, key);	
	if(key > ptr->key)
		return search(ptr->right, key);	
}

void existed(node* root, int key)
{
	if(search(root, key) != NULL)
		printf("There is a node equals %d in the BST.\n", key);
	else
		printf("There is not a node equals %d in the BST.\n", key);
}
