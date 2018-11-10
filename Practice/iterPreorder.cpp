/* binary tree is 
		 1
	  2    3
    4  5  6
*/

#include<iostream>
#include<stack>

using namespace std;

// the node of tree
typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
}node;

node *create(int);			// helper function
void preorder(node *);

int main()
{
	node *root = create(1);
	root->left = create(2);
	root->right = create(3);
	root->left->left = create(4);
	root->left->right = create(5);
	root->right->left = create(6);
	
	preorder(root);
	
	return 0;
}

node* create(int data)
{
	node *newNode = new node;
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void preorder(node *root)		// root, left, right
{
	if(root == NULL)
		return;
		
	// create an empty stack
	stack<node *> s;
	s.push(root);
	
	// pop and remember the property of stack is LIFO
	while(!s.empty())
	{
		node *node = s.top();
		printf("%d ", node->data);
		s.pop();
		
		if(node->right)
			s.push(node->right);
		if(node->left)
			s.push(node->left);
	}
}
