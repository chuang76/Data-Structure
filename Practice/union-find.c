// use union-find algo te detect cycle in a graph

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct edge
{
	int src, dest;
}edge;

typedef struct graph
{
	int V, E;		// number of vertices and edges
	edge* e;		// ���V edges 
}graph;

graph* create(int V, int E)		// utility function to create a graph
{
	graph* g = malloc(sizeof(graph));	
	g->V = V;
	g->E = E;
	g->e = malloc(g->E * sizeof(edge));
	return g;
}

int find(int parent[], int i)
{
	if(parent[i] == -1)
		return i;
	else
		find(parent, parent[i]);		// �~�򩹤W�� 
}

void Union(int parent[], int x, int y)
{
	int xset = find(parent, x);			// ���T�w��Ӹ`�I�ݩ󤣦P���X 
	int yset = find(parent, y);
	
	if(xset != yset)
		parent[xset] = yset;			// �� x �֨� y �h 
}

int isCycle(graph *g)
{
	int *parent = malloc(g->V * sizeof(int));
	
	memset(parent, -1, g->V * sizeof(int)); 	// �������] -1 (�C�Ӹ`�I�@�}�l�� root) 

	for(int i = 0; i < g->E; i++)		// �u�����ˬd 
	{
		int x = find(parent, g->e[i].src);		// ��� , �^�ǩҳB���X�N��H�� 
		int y = find(parent, g->e[i].dest);
		
//		for(int j = 0; j < g->V; j++)
//			printf("%d ", parent[j]);
//		printf("\n");
		
		if(x == y)
			return 1;
		else
			Union(parent, x, y);
	}
	return 0;
}

int main(void)
{
	int V = 4, E = 4;
	graph *g = create(V, E);
	
	g->e[0].src = 0;		// tree is a acyclic graph
	g->e[0].dest = 1;
	
	g->e[1].src = 0;
	g->e[1].dest = 2;
		
	g->e[2].src = 2;
	g->e[2].dest = 3;
	
//	g->e[3].src = 1;
//	g->e[3].dest = 2;
	
	if(isCycle(g))
		printf("graph contains cycle\n");
	else
		printf("graph does not contain cycle\n");
		
	return 0;
}

