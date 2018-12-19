/*
 *   the properties of binary heap :
 *   1. is a complete binary tree
 *   2. is either min heap or max heap
 */
 
#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct
{
	int data;
}node;

node heap[MAX];		// 索引值從 1 開始 
int count = 0;

void HeapFull()
{
	printf("The heap is full.\n");
	exit(0);
}

void HeapEmpty()
{
	printf("The heap is empty.\n");
	exit(0);
}

void swap(node *i, node *j)
{
	node *t;
	t = i;
	i = j;
	j = i;
}

void push(node n)
{
	int i;
	
	if(count == MAX - 1)
		HeapFull();
	else
	{
		count++;
		i = count;
		while((i != 1) && (n.data > heap[i / 2].data))
		{
			heap[i] = heap[i / 2];
			i /= 2;
		}
		heap[i] = n;
	}
}

node pop()
{
	int i, j;
	node n;
	
	if(count == 0)
		HeapEmpty();
	else
	{
		n = heap[1];
		heap[1] = heap[count];			// 最末端移到 root
		count--;
		
		i = 1;
		while(i <= count / 2)
		{
			if(heap[2 * i].data > heap[2 * i + 1].data)
				j = 2 * i;
			else
				j = 2 * i + 1;
			
			if(heap[i].data > heap[j].data)
				break;
			swap(&heap[i], &heap[j]);
			i = j;						// swap 完一輪, 將 i 改成 j, 繼續往下一層檢查 
		} 
		return n;
	}
}

int main(void)
{
	int value[9] = {7, 16, 49, 82, 5, 31, 6, 2, 44};
	node n[9];
	
	for(int i = 0; i < 9; i++)
	{
		n[i].data = value[i];
		push(n[i]);
	}
	
	for(int i = 1; i <= count; i++)
		printf("%d ", heap[i].data);
	printf("\n");
	
	return 0;
}
