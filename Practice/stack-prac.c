#include<stdio.h>
#include<stdlib.h>
#define MAX 5

int s[MAX];
int top = -1;
void push(int);
int pop();
int Top();
int isEmpty();

int main(void)
{
	while(1)
	{
		int n, v;
		printf("Select the choice 1)push 2)pop 3)top 4)isEmpty : ");
		scanf("%d", &n);
	
		switch(n)
		{
			case 1:
				printf("Input the number: ");
				scanf("%d", &v);
				push(v);
				break;
			case 2:
				printf("the number which is poped is %d\n", pop());
				break;
			case 3:
				printf("the number which is top is %d\n", Top());
				break;
			case 4:
				if(isEmpty())
					printf("is empty\n");
				else
					printf("is not empty\n");
				break;
		}
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

void push(int v)
{
	top++;
	s[top] = v;
}

int pop()
{
	return s[top--];
}

int Top()
{
	return s[top];
}
