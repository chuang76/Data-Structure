// insertion sort

#include<stdio.h>
#include<stdlib.h>

void sort(int[], int);

int main(void)
{
	int arr[] = {12, 3, 8, 7, 4};
	int n = sizeof(arr) / sizeof(arr[0]);
	
	sort(arr, n);
	for(int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
	
	return 0;
}

void sort(int arr[], int n)
{
	int key, j;
	for(int i = 0; i < n; i++)
	{
		key = arr[i];			// key moves right
		j = i - 1;
		
		while(j >= 0 && arr[j] > key)		// find the right position
		{
			int tmp = arr[j+1];
			arr[j+1] = arr[j];
			arr[j] = tmp;
			j = j - 1;
		}
	}
}

