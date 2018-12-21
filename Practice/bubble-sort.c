// bubble sort
#include<stdio.h>
#include<stdlib.h>

void sort(int[], int);

int main(void)
{
	int arr[] = {57, 32, 86, 12, 23, 92, 14};
	int n = sizeof(arr) / sizeof(arr[0]);
	
	sort(arr, n);
	for(int i = 0; i < n; i++)
		printf("%d ", arr[i]);		
	printf("\n");
	
	return 0;
}

void sort(int arr[], int n)
{
	for(int i = 0; i < n-1; i++)		// 材碭近 –近暗Ч常絋﹚程竚 
	{
		for(int j = 0; j < n-i-1; j++)		// ㄢㄢ綟じ秈︽ゑ耕 
		{
			if(arr[j] > arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

