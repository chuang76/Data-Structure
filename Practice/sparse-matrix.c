// Sparse Matrix 
// 多數元素沒有資料, 為避免記憶體空間浪費, 因此設計稀疏矩陣以較少的記憶體來儲存 

#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	// 5 * 6 的 matrix, 且其中有 4 個 element 有值 
	int num[5][3] = {{5, 6, 4}, {1, 1, 3}, {2, 3, 6}, {3, 2, 9}, {4, 4, 12}}; 
	
	int i, j, k = 1;
	for(i = 0; i < num[0][0]; i++)
	{
		for(j = 0; j < num[0][1]; j++)
		{
			if(k <= num[0][2] && i == num[k][0] && j == num[k][1])
			{
				printf("%4d", num[k][2]);
				k++;
			}	
			else
				printf("%4d", 0);
		}
		printf("\n");
	}
	
	system("pause");
	return 0;
}
