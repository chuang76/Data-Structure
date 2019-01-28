/*
 *   Title : binary insertion sort
 *	 Idea : binary search + insert 
 */

#include<stdio.h>
#include<stdlib.h>

int search(int [], int, int, int);		
void sort(int [], int);

int main(void)
{
//	int arr[] = {12, 8, 93, 26, 65, 47};
	int arr[] = {23, 56, 11, 3, 45, 82, 109, 37};
	int n = sizeof(arr) / sizeof(arr[0]);
	
	sort(arr, n);
	
	for(int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
	
	return 0;
}

int search(int arr[], int data, int low, int high)		// return location where data should be inserted
{
	if(high <= low)
		return (data > arr[low]) ? (low + 1) : low;
	
	int mid = (high + low) / 2;
	
	if(data == arr[mid])
		return mid + 1;				// 比較晚來放後面 
	else if(data > arr[mid])
		return search(arr, data, mid+1, high);
	else
		return search(arr, data, low, mid-1);
}

void sort(int arr[], int n)
{
	for(int i = 1; i < n; i++)
	{
		int key = arr[i];		// 要調整的 
		
		int loc = search(arr, key, 0, i-1);			// 0 到 i - 1 
		
//		printf("i = %d key = %d loc = %d ", i, key, loc);

//		for(int j = loc; j < i; j++)				// 不能直接往後移 , 會被蓋掉 
//		{
//			arr[j+1] = arr[j];
//		}
//		arr[loc] = key;

		for(int j = i; j > loc; j--)
			arr[j] = arr[j-1];
		arr[loc] = key;
		
	}
}
