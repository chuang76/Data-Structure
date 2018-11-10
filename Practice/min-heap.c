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
		
		while(i != 1 && n.data < heap[i/2].data)		// ���W�ˬd 
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
		node n;						// ���ӱ� root
		
		n = heap[1];
		heap[1] = heap[count];		// �̥��ݮ��Ӹ� root ����m
		count--;
		
		i = 1;						// �H�e�O�̥��ݲ{�b����m 
		while(i <= count / 2)		// �X�h
		{
			heap[2 * i].data < heap[2 * i + 1].data ? (j = 2 * i) : (j = 2 * i + 1);  // �ݥ��� leftchild �M rightchild
			
			if(heap[i].data < heap[j].data)		 
				break;
				
			swap(&heap[i], &heap[j]);
			i = j;						// i ��s�� j, �~�򩹤U�ˬd 
		} 
		return n;						// �^�ǭ�Ӫ� root, pop �X�h 
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
