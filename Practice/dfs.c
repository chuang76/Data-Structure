// dfs practice

#include<stdio.h>
#include<stdlib.h>
#define MAX 20

typedef struct node
{
	int data;
	struct node *next;
}node;

node* head[MAX];
int visited[MAX];		// �����O�_���X�L
int size;				// �`�@�X�� vertex 
void input(); 
void create(int, int);
void dfs(int);

int main(void)
{
	input();
	
	for(int i = 0; i < size; i++)
		visited[i] = 0;			// initialization
	
	int start;
	printf("Enter the start point: ");
	scanf("%d", &start);
	printf("The traversal of DFS: ");	
	dfs(start);			// �q 2 �}�l���X 
}

void input()
{
	printf("Enter the number of vertices: ");
	scanf("%d", &size);
	
	for(int i = 0; i < size; i++)
		head[i] = NULL;			// �����V null
		
	int e;
	printf("Enter the number of edges: ");
	scanf("%d", &e);
		
	for(int j = 0; j < e; j++)
	{
		int u, v;
		printf("Enter edge(u, v): ");
		scanf("%d %d", &u, &v);
		create(u, v);
	} 
}

void create(int u, int v)
{
	node* n = malloc(sizeof(node));
	n->data = v;
	n->next = NULL;
	
	node *ptr;
	if(head[u] == NULL)
		head[u] = n;		// ���V n 
	else
	{
		ptr = head[u];
		
		while(ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = n;
	}
}

void dfs(int i)
{
	printf("%d ", i);
	visited[i] = 1;
	
	node* ptr;
	ptr = head[i];
	
	while(ptr != NULL)
	{
		i = ptr->data;
		if(!visited[i])
			dfs(i);
		ptr = ptr->next;
	}
}

