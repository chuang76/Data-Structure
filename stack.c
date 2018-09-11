// 因為c/c++不能傳遞二維陣列, 所以用struct包起來傳 
#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct coordinate
{
	int x;
	int y;
} coo;

coo stack[MAX];
int top = -1;
int isEmpty();
void push(coo);
coo pop();

int main(void)
{
	int i;
	for(i = 0; i < 5; i++)
	{
		int a, b;
		coo c1;
		printf("Enter the numbers: ");
		scanf("%d %d", &a, &b);
		c1.x = a;
		c1.y = b;
		push(c1);
	}
	printf("===================================\n");
	while(!isEmpty())
	{
		coo c2;
		c2 = pop();
		printf("%d %d\n", c2.x, c2.y);
	}
	
	system("pause");
	return 0;
}

int isEmpty()
{
	if(top == -1)
		return 1;
	else
		return 0;
}

void push(coo c1)
{
	if(top >= MAX)
		printf("堆疊已滿\n");
	else
	{
		top++;
		stack[top] = c1;
	}
}

coo pop()
{
	coo c2;
	if(isEmpty())
		printf("堆疊已空\n");
	else
	{
		c2 = stack[top];
		top--;
		return c2;
	}
}

