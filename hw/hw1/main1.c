#include<stdio.h>
#include<stdlib.h>

int count = 1, org[15][16], a[17][17] = {0}, b[17][17] = {0}, sum[120] = {0};
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
void dfs(int, int);
void Max();

int main(void)
{
	FILE *fp;
	fp = fopen("input.txt","r");			// read the file only by pointer
	
	int i, j;	 
	char c;		
	for(i = 0; i < 15; i++)
	{
		for(j = 0; j < 16; j++)
		{
			fscanf(fp, "%c", &c);			// read the characters one by one 
			org[i][j] = c - 48;
		}
		org[i][15] = 0;
	}
	fclose(fp);								// remember to close the pointer
	
	for(i = 0; i < 15; i++)
		for(j = 0; j < 15; j++)
			a[i+1][j+1] = org[i][j];
	
	printf("Original Lake\n");				// print the map of original lake 
	for(i = 1; i < 16; i++)
	{
		for(j = 1; j < 16; j++)
			printf("%3d", a[i][j]);
		printf("\n");
	}
	
	for(i = 1; i < 16; i++)
	{
		for(j = 1; j < 16; j++)
		{
			if(a[i][j] != 0 && b[i][j] == 0)
			{
				b[i][j] = count;
				count++;
				dfs(i,j);
			}
		}
	}
		
	printf("\nResult Lake\n");
	Max();
	
	system("pause");
	return 0;
}

void dfs(int i, int j)		// search beginning at a[i][j]
{
	int k;
	for(k = 0; k < 4; k++)
	{
		int tx = i + dx[k];
		int ty = j + dy[k];
		if(a[tx][ty] != 0 && b[tx][ty] == 0)
		{
			b[tx][ty] = b[i][j];
			dfs(tx,ty);
		}
	}
}

void Max()
{
	count = count - 1;
	int i, j, k, c[120];
	for(i = 0; i < count; i++)		// from 1 to count
		c[i] = i + 1;
	
	for(i = 1; i < 16; i++)
		for(j = 1; j < 16; j++)
			for(k = 0; k < count; k++)
				if(b[i][j] == c[k])
					sum[k] += a[i][j];
	
	int max = sum[0], index = 0;			// compare
	for(i = 0; i < count; i++)
	{
		if(sum[i] >= max)
		{
			max = sum[i];
			index = i;
		}
	}
		
	index += 1;
	for(i = 1; i < 16; i++)				// print the map of the result lake
	{
		for(j = 1; j < 16; j++)
		{
			if(b[i][j] == index)
				printf("%3d", a[i][j]);
			else
				printf("  *");
		}
		printf("\n");
	}
	
	printf("\nThe coordinates of the largest lake\n");		// print the coordinates
	for(i = 1; i < 16; i++)
		for(j = 1; j < 16; j++)
			if(b[i][j] == index)
				printf("(%d,%d)\n", i-1, j-1);
	
	printf("\nThe volume of the largest lake is %d\n", max);		// print the volume
}

