// graph representation practice: use adjacent list

#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node;

typedef struct list			// represent a adjacent list
{
	node *head;
}list;

typedef struct graph
{
	int V;					// number of vertices
	list *arr;
}graph;

node* newNode(int data)		// utility function to create a node
{
	node *n = malloc(sizeof(node));
	n->data = data;
	n->next = NULL;
	return n;
}

graph* newGraph(int V)
{
	graph *g = malloc(sizeof(graph));
	g->V = V;
	g->arr = malloc(V * sizeof(list));
	
	for(int i = 0; i < g->V; i++)
		g->arr[i].head = NULL;				// initialization
	
	return g;
}

void newEdge(graph* g, int src, int dest)
{
	node *n;
	if(g->arr[src].head == NULL)
	{
		n = newNode(src);
		g->arr[src].head = n;	
	}
	
	node *m;
	m = newNode(dest);
	n = g->arr[src].head;
	while(n->next != NULL)
		n = n->next;
	n->next = m;		
}

int main(void)
{
	int V = 4;
	graph *g = newGraph(V);
	
	newEdge(g, 0, 1);
	newEdge(g, 0, 2);
	newEdge(g, 2, 0);
	newEdge(g, 1, 2);
	newEdge(g, 2, 3);
	newEdge(g, 3, 3);
	
	for(int i = 0; i < g->V; i++)
	{
		node* ptr = g->arr[i].head;
		
		while(ptr != NULL)
		{
			printf("%d ", ptr->data);
			ptr = ptr->next;
		}
		printf("\n");
	}	
}

