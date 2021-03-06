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
	for(int i = 0; i < n-1; i++)		// 第幾輪 每一輪做完都可以確定好一個最大值的位置 
	{
		for(int j = 0; j < n-i-1; j++)		// 兩兩相鄰元素進行比較 
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

