// Generate an array randomly
// use selection sort to transform the array into an ordered list
// use binary search to search the number which you want, return the index of the number

#include<stdio.h>
#include<math.h>
#include<time.h>
#define MAX_SIZE 101

int main(void)
{
	srand(time(NULL));			
	int arr[MAX_SIZE];
	int i, j, n, temp;
	printf("Enter the number of numbers to generate: ");
	scanf("%d", &n);
	
	if(n < 1 || n > MAX_SIZE)
	{
		printf("Improper value of n\n");
		exit(0);
	}
				
	for(i = 0; i < n; i++)					// generate the numbers randomly
		arr[i] = rand() % 1000;				// the range is 0 - 1000
			
	for(i = 0; i < n-1; i++)				// selection sort
	{
		for(j = i+1; j < n; j++)
		{
			if(arr[j] < arr[i])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	
	for(i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
	
	int num;
	printf("Enter the number which you want to search: ");
	scanf("%d", &num);
	
	int left = 0;							// binary search
	int right = n - 1;
	int middle;
	while(left <= right)
	{
		middle = (left + right) / 2;	
		// printf("middle = %d\n", middle);
		if(num < arr[middle])
			right = middle - 1;
		else if(num > arr[middle])
			left = middle + 1;
		else
			break;
	}
	printf("index: %d\n", middle);
	
	system("pause");
	return 0;
}
