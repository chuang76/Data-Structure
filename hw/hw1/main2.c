#include<stdio.h>
#include<stdlib.h>

int count = 1, org[15][16], a[17][17] = {0}, b[17][17] = {0}, sum[120] = {0};
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
void dfs(int, int);
void Max();
void connect();

int main(void)
{
	FILE *fp;
	fp = fopen("input1.txt","r");			// read the file only by pointer
	
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

	Max();
	connect();
	
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
	int i, j, k, c[count];
	for(i = 0; i < count; i++)		// from 1 to count
		c[i] = i + 1;
	
	for(i = 1; i < 16; i++)
		for(j = 1; j < 16; j++)
			for(k = 0; k < count; k++)
				if(b[i][j] == c[k])
					sum[k] += a[i][j];		
}

void connect()
{
	int i, j, k, arr[30][2] = {0}, x = 0; 
	
	for(i = 1; i < 16; i++)
	{
		if(b[i][1] != 0 && b[i][15] != 0) 		// b[i][1] is connected with b[i][15]
		{
			arr[x][0] = b[i][1];		 // record which lake it is
			arr[x][1] = b[i][15];
			x++;
		}
	}

	for(j = 1; j < 16; j++)
	{
		if(b[1][j] != 0 && b[15][j] != 0)		// b[1][j] is connected with b[15][j]
		{
			arr[x][0] = b[1][j];
			arr[x][1] = b[15][j];
			x++;
		}
	}

	int m[115][115] = {0};			// adjacency matrix
	for(i = 0; i < x; i++)
	{
		m[arr[i][0]][arr[i][1]] = 1;
		m[arr[i][1]][arr[i][0]] = 1;
	}
	
	int max = sum[0], index = 1;			// to add up and compare
	for(i = 1; i <= count; i++)
	{
		int temp = sum[i-1]; 
		for(j = 1; j <= count; j++)
		{
			if(m[i][j] == 1 && i!= j)
				sum[i-1] = sum[i-1] + sum[j-1];			// i is the main lake, j is the additional lake
			if(sum[i-1] >= max)
			{
				max = sum[i-1];
				index = i;
			}
		}
		sum[i-1] = temp;
	}
	
	printf("The volume of the largest lake\n%d\n", max);
	
	printf("The coordinates of the largest lake\n");
	
	for(i = 1; i < 16; i++)
		for(j = 1; j < 16; j++)
			if(b[i][j] == index)
				printf("(%d,%d)\n", i-1, j-1);		// print the coordinates of the main lake
				
	for(k = 1; k <= count; k++)
		if(m[index][k] == 1 && index != k)
			for(i = 1; i < 16; i++)
				for(j = 1; j < 16; j++)
					if(b[i][j] == k)
						printf("(%d,%d)\n", i-1, j-1);		// print the coordinates of the additional lake
}

