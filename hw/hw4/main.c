/* 
 *   Title : Knight Problem
 *	 Date : Dec, 2018
 */
#include<stdio.h>
#include<stdlib.h>

typedef struct coord
{
	int x, y;
}coord;

coord src;
coord dest;
coord queue[64];		// use for bfs
coord path[64];			
int front, rear;		// 0
int size = 0;			// for path
int count = 0;
int visited[10][10] = {0};
int dx[] = {-1, -2, -2, -1, 1, 2, 2, 1};
int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
void bfs(coord);
void dfs(coord);
void init();

int main(void)
{
	FILE *fp;
	fp = fopen("input.txt", "r");
	
	int n;
	fscanf(fp, "%d", &n);
	
	for(int i = 0; i < n; i++)
	{
		int m;
		fscanf(fp, "%d", &m);			// mode
		printf("Mode %d\n", m);
		init();
		
		if(m == 1)
		{
			while(fscanf(fp, "%d %d %d %d", &src.x, &src.y, &dest.x, &dest.y))
			{
				if((src.x + src.y + dest.x + dest.y) == 0)
					break;
				queue[0] = src;
				rear++; 
				bfs(src);
				
				path[0] = src;
				size++;
				dfs(src);
				
				printf("Step: %d\n", visited[dest.x][dest.y]-1);
				init();	
			}
			printf("\n");
		}
		if(m == 2)
		{
			int obs;
			fscanf(fp, "%d", &obs);
			
			for(int j = 0; j < obs; j++)
			{
				coord tmp;
				fscanf(fp, "%d %d", &tmp.x, &tmp.y);
				visited[tmp.x][tmp.y] = -1;
			}
			
			while(fscanf(fp, "%d %d %d %d", &src.x, &src.y, &dest.x, &dest.y))
			{
				if((src.x + src.y + dest.x + dest.y) == 0)
					break;
				
				queue[0] = src;
				rear++; 
				bfs(src);
				
				path[0] = src;
				size++;
				dfs(src);
				if(count == 0)
				{
					size = count = front = rear = 0;
					for(int j = 0; j < 10; j++)
						for(int k = 0; k < 10; k++)
							if(visited[j][k] != -1)
								visited[j][k] = 0;
					printf("NULL\n");
					continue;
				}
				
				printf("Step: %d\n", visited[dest.x][dest.y]-1);	// since visited[src] is 1
				size = count = front = rear = 0;
				for(int j = 0; j < 10; j++)
					for(int k = 0; k < 10; k++)
						if(visited[j][k] != -1)
							visited[j][k] = 0;
			}
			printf("\n");
		}
		
		if(m == 3)
		{
			int num;
			fscanf(fp, "%d", &num);
			
			coord knight[64];
			for(int j = 0; j < num; j++)
				fscanf(fp, "%d %d", &knight[j].x, &knight[j].y);
			fscanf(fp, "%d %d", &dest.x, &dest.y);
			visited[dest.x][dest.y] = 1;
			
			queue[0] = dest;
			rear++;
			bfs(dest);
			int sum = 0;
			for(int j = 0; j < num; j++)
				sum += visited[knight[j].x][knight[j].y];
			printf("Step: %d\n\n", sum-num);
		}
	}
	fclose(fp);
	return 0;
}

void init()			// initialization
{
	size = count = front = rear = 0;
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 10; j++)
			visited[i][j] = 0;
}

void bfs(coord c)
{
	visited[c.x][c.y] = 1;
	
	while(front != rear)		// queue is not empty 
	{
		for(int i = 0; i < 8; i++)
		{
			coord tmp;
			tmp.x = queue[front].x + dx[i];
			tmp.y = queue[front].y + dy[i];
			if(tmp.x < 1 || tmp.y < 1 || tmp.x > 8 || tmp.y > 8)		// avoid the coordinate out of range
				continue;
			if(visited[tmp.x][tmp.y] == 0)		// can be arrived
			{
				queue[rear] = tmp;
				visited[tmp.x][tmp.y] = visited[queue[front].x][queue[front].y] + 1; 
				if(tmp.x == dest.x && tmp.y == dest.y)
					return;		// find
				rear++;
			}
		}
		front++;
	}
}

void dfs(coord c)			// trace the path
{
	for(int i = 0; i < 8; i++)
	{
		coord tmp;
		tmp.x = c.x + dx[i];
		tmp.y = c.y + dy[i];
		
		if(tmp.x < 1 || tmp.y < 1 || tmp.x > 8 || tmp.y > 8)		// avoid the coordinate out of range
			continue;
		if(visited[tmp.x][tmp.y] != visited[c.x][c.y] + 1)
			continue;
			
		path[size++] = tmp;
		
		if(tmp.x == dest.x && tmp.y == dest.y && count == 0)		// find the destination
		{
			printf("Path: ");
			for(int j = 0; j < size; j++)
				printf("(%d,%d)", path[j].x, path[j].y);
			printf("\n");
			count++;
//			return;
		}
		dfs(tmp);
		size--;			// means pop 
	}
}
