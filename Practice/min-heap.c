#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct
{
	int data;
}node;

node heap[MAX];
int count = 0;

void HeapFull()
{
	printf("The heap is full.\n");
	exit(1);
}

void HeapEmpty()
{
	printf("The heap is empty.\n");
	exit(1);
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
	if(count == MAX - 1)
		HeapFull();
	else
	{
		count++;
		int i = count;
		
		while(i != 1 && n.data < heap[i/2].data)		// 往上檢查 
		{
			heap[i] = heap[i/2];
			i /= 2;
		}
		heap[i] = n;
	}
}

node pop()
{
	if(count == 0)
		HeapEmpty();
	else
	{
		int i, j;
		node n;						// 拿來接 root
		
		n = heap[1];
		heap[1] = heap[count];		// 最末端拿來補 root 的位置
		count--;
		
		i = 1;						// 以前是最末端現在的位置 
		while(i <= count / 2)		// 幾層
		{
			heap[2 * i].data < heap[2 * i + 1].data ? (j = 2 * i) : (j = 2 * i + 1);  // 看它的 leftchild 和 rightchild
			
			if(heap[i].data < heap[j].data)		 
				break;
				
			swap(&heap[i], &heap[j]);
			i = j;						// i 更新成 j, 繼續往下檢查 
		} 
		return n;						// 回傳原來的 root, pop 出去 
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
