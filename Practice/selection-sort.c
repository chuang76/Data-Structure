// selection sort
#include<stdio.h>
#include<stdlib.h>

void sort(int[], int);

int main(void)
{
//	int arr[] = {12, 3, 8, 7, 4};
	int arr[] = {34, 35, 11, 96, 78, 56};

	int n = sizeof(arr) / sizeof(arr[0]);
	
	sort(arr, n);
	for(int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
	
	return 0;
}

void sort(int arr[], int n)
{
	for(int i = 0; i < n-1; i++)
	{
		int min = i;
		for(int j = i+1; j < n; j++)
		{
			if(arr[j] < arr[min])
				min = j;
		}
		
		if(min != i)		// swap
		{
			int temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}
