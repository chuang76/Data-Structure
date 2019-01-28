/*	 
 *  Title: Complete binary tree
 *  Idea: Use the properties of CBT to solve the problem 
 *  Date: Dec, 2018
 */
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	char data;
	int weight;
}node;

node arr[30];

int main(void)
{
	FILE *fp;
	fp = fopen("input2.txt", "r");
	char s[240];
	while(fscanf(fp, "%s", s) != EOF)			//  stops when recognizing '\n'
	{
		char *token;
		token = strtok(s, ",()");
		int idx, size;
		idx = size = 0;
		
		while(token)
		{
			if(idx % 2 == 0)
				sscanf(token, "%c", &arr[size].data);
			else
			{
				sscanf(token, "%d", &arr[size].weight);
				size++;
			}
			idx++;
			token = strtok(NULL, ",()");
		}
		int m;
		for(int i = 0; i < size; i++)
		{
			if((2*i+1) >= size)
			{
				m = i;
				break;
			}
			arr[2*i+1].weight += arr[i].weight;
			arr[2*i+2].weight += arr[i].weight;
		}
		int min = m;
		for(int i = m; i < size; i++)
			if(arr[i].weight < arr[min].weight)
				min = i;
		
		int list[5] = {0};		// log26
		int n = 0;
		while(min != 0)
		{
			list[n] = min;
			n++;
			min = (min - 1) / 2;
		}
		printf("Path: ");
		for(int i = n ; i >= 0; i--)
			printf("%c", arr[list[i]].data);
		printf("\nWeight: %d\n\n", arr[list[0]].weight);
	}
	return 0;
}
