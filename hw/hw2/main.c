#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct st           	// use the structure to implement cities 
{
	char name[15];
	int w;
	int next[60];		// use int type to store index
	int count;
}city[60];

typedef struct node
{
	char data[15];
	struct node *pre;
	struct node *next;
}node;

node *head[100];
node *ptr[100];		

node *chead[100];
node *cptr[100];

void init();
void first();
void array(char *);
void bcity(char *, int);		// build  cities
void bnext();
int map(char *);				// return the index of city
void dfs(int);

void findCycle(int);
void copy(int);
void copyCycle(int);
void ans();
void save();					// store the index of city from Q2
void compare();

void q1();
void q2();
void q3();
void q4();

FILE *fp;	
char sp[15], ep[15];		// start point and end point
int weight;					// weight of goods

char arr[2500][2][15];		// store the cities which are connected
int visited[60] = {0};
int arrive[60] = {0};
int arr_size = 0;
int city_size = 0;
int path = 0;
int cpath = 0;

int main(void)
{
	fp = fopen("input.txt", "r");		// read the file
	init();
	first();							// read the first line, include the start point and the end point
	
	char s[1000];						// suppose 50 cities * 10 characters and others
	while(fscanf(fp, "%s\n", s) != EOF)	// line by line
	{
		if(strcmp(s, "0") == 0)			// if string s and "0" are the same, print the answer
		{
			q1();
			q2();
			q3();
			q4();
			printf("\n");
			init();	
			for(int i = 0; i < path; i++)
			{
				free(head[i]);
				free(ptr[i]);
			}
			first();					
		}
		else if(strcmp(s, "-1") == 0)	// print the answer
		{
			q1();
			q2();
			q3();
			q4();
			printf("\n");
			break;						// end
		}
		else							// tokenize
		{
			int index = 0; 				// to identify whether it is the first operation 
			char *token;
			token = strtok(s, "->");
			
			while(token)
			{
				char a[15];		// name of city
				int b;			// weight 
				
				sscanf(token, "%[^,],%d", a, &b);
				bcity(a, b);
				
				if(index == 0)						// first time
				{
					strcpy(arr[arr_size][0], a);
					index = 1;
				}
				else
					array(a);
				token = strtok(NULL, "->");
			}
		}
	}
	fclose(fp);		// close the file
	
	return 0;
}

void init()			// initialize
{
	for(int i = 0; i < arr_size; i++)
	{
		arr[i][0][0] = '\0';
		arr[i][1][0] = '\0';
	}
	arr_size = 0;
	
	for(int i = 0; i < city_size; i++)
	{
		city[i].name[0] = '\0';
		city[i].w = 0;
		city[i].count = 0;
	}
	city_size = 0;
	
	path = 0;
	cpath = 0;
	
	for(int i = 0; i < 60; i++)
	{
		visited[i] = 0;
		arrive[i] = 0;
	}
		
}

void first()			
{
	fscanf(fp, "%[^,],%[^,],%d\n", sp, ep, &weight);
}

void array(char *a)
{
	strcpy(arr[arr_size][1], a);
	arr_size++;
	strcpy(arr[arr_size][0], a);
}

void q1()			// bubble sort
{
	for(int i = 0; i < arr_size - 1; i++)
	{
		for(int j = 0; j < arr_size - i - 1; j++)
		{
			if(strcmp(arr[j][0], arr[j+1][0]) == 1)
			{
				char temp[15];
				strcpy(temp, arr[j][0]);
				strcpy(arr[j][0], arr[j+1][0]);
				strcpy(arr[j+1][0], temp);
				
				strcpy(temp, arr[j][1]);
				strcpy(arr[j][1], arr[j+1][1]);
				strcpy(arr[j+1][1], temp);
			}
			else if(strcmp(arr[j][0], arr[j+1][0]) == 0)
			{
				if(strcmp(arr[j][1], arr[j+1][1]) == 1)
				{
					char temp[15];
					strcpy(temp, arr[j][1]);
					strcpy(arr[j][1], arr[j+1][1]);
					strcpy(arr[j+1][1], temp);
				}
			}
		}
	}
	
	printf("Map:\n");	
	for(int i = 0; i < arr_size; i++)
	{
		if(i != 0)
			if(strcmp(arr[i][0], arr[i-1][0]) == 0 && strcmp(arr[i][1], arr[i-1][1]) == 0)   // skip the same
				continue;
		printf("%s,%s\n", arr[i][0], arr[i][1]);
	}
	if(arr_size == 0)
		printf("NULL\n");
}

void q2()
{
	bnext(); 
	
	printf("All the paths from city %s to city %s :\n", sp, ep);
	if(strcmp(sp, ep) == 0)
	{
		printf("NULL\n");
		return;
	}
	
	head[0] = malloc(sizeof(node));
	strcpy(head[0]->data, sp);			// store start point into the head[0]
	head[0]->pre = NULL;
	head[0]->next = NULL;
	ptr[0] = head[0];
	
	visited[map(sp)] = 1;
	dfs(map(sp));
	visited[map(sp)] = 0;
	
	if(path == 0)
		printf("NULL\n");
	else	
		ans();
}

void bcity(char *a, int b)
{
	for(int i = 0; i < city_size; i++)
		if(strcmp(city[i].name, a) == 0)		// exists in cities
			return;
			
	strcpy(city[city_size].name, a);
	city[city_size].w = b;
	city_size++; 
} 

void bnext()
{
	for(int i = 0; i < arr_size; i++)
	{
		int a = map(arr[i][0]);
		int b = map(arr[i][1]);
		int c = city[a].count;
		
		if(c != 0 && city[a].next[c-1] == b)
			continue;	
			
		city[a].next[c] = b;
		city[a].count++;
	}
}

int map(char *n)
{
	for(int i = 0; i < city_size; i++)
		if(strcmp(city[i].name, n) == 0)
			return i;
	return 50;				// there are 49 cities at most
}

void dfs(int n)				// start point
{
	for(int i = 0; i < city[n].count; i++)
	{
		if(strcmp(city[city[n].next[i]].name, ep) == 0)
		{
			node *newNode = malloc(sizeof(node));		// create a node for the ptr
			strcpy(newNode->data, ep);
			ptr[path]->next = newNode;
			newNode->pre = ptr[path];
			newNode->next = NULL;
			ptr[path] = newNode;
			path++;
			
			copy(path);						
			ptr[path] = ptr[path]->pre;
			free(ptr[path]->next);
			ptr[path]->next = NULL;			
			
		}
		else if(visited[city[n].next[i]] == 0)			// does not exist
		{
			visited[city[n].next[i]] = 1;
			
			node *newNode = malloc(sizeof(node));
			strcpy(newNode->data, city[city[n].next[i]].name); 
			newNode->pre = ptr[path];
			ptr[path]->next = newNode;
			newNode->next = NULL;
			ptr[path] = newNode; 
			
			dfs(city[n].next[i]);	
			
			ptr[path] = ptr[path]->pre;
			free(ptr[path]->next);
			ptr[path]->next = NULL;
			
			visited[city[n].next[i]] = 0;
		}
	}
}

void copy(int n)		// copy the path from the last one
{
	head[n] = malloc(sizeof(node));
	strcpy(head[n]->data, sp);
	head[n]->pre = NULL;
	head[n]->next = NULL;
	
	node *p, *tp;
	p = head[n];
	tp = head[n-1]->next;		// the last one
	
	while(tp != NULL)
	{
		node* newNode = malloc(sizeof(node));
		strcpy(newNode->data, tp->data);
		newNode->pre = p;
		p->next = newNode;
		newNode->next = NULL;
		p = newNode;
		tp = tp->next;
	}
	ptr[n] = p;	
}

void ans()
{
	node *p;
	for(int i = 0; i < path; i++)
	{
		p = head[i];
		while(p != NULL)
		{
			if(p != ptr[i])					// if it is not end point
				printf("%s,", p->data);
			else
				printf("%s\n", p->data);
			p = p->next;
		}
	}
}

void q3()
{
	printf("All the best paths from city %s to city %s :\n", sp, ep);
	
	node *p;
	int count = 0;
	
	for(int i = 0; i < path; i++)
	{
		int index = 0;
		p = head[i];
		while(p != NULL)
		{
			if(city[map(p->data)].w < weight)		// can not load the goods
			{
				index = 1;
				break;
			}
			p = p->next;
		}
		
		p = head[i];
		if(index == 0)
		{
			while(p != NULL)
			{
				if(p != ptr[i])
					printf("%s,", p->data);
				else
					printf("%s\n", p->data);
				p = p->next;
			}
			count++;
		}
	}
	if(count == 0)
		printf("NULL\n");
}

void q4()
{
	printf("All the paths has circle from city %s to city %s :\n", sp, ep);
	
	chead[0] = malloc(sizeof(node));		// the idea is similar to Q2
	strcpy(chead[0]->data, sp);
	chead[0]->pre = NULL;
	chead[0]->next = NULL;
	cptr[0] = chead[0];
	
	visited[map(sp)] = 1;
	findCycle(map(sp));
	visited[map(sp)] = 0;
	save();
	
	if(cpath == 0)
		printf("NULL\n");
	else
		compare();
}

void findCycle(int n)
{
	for(int i = 0; i < city[n].count; i++)
	{
		if(strcmp(city[city[n].next[i]].name, ep) == 0)
			continue;
		if(visited[city[n].next[i]] == 1)
		{
			node *newNode = malloc(sizeof(node));
			strcpy(newNode->data, city[city[n].next[i]].name);
			cptr[cpath]->next = newNode;
			newNode->pre = cptr[cpath];
			newNode->next = NULL;
			cptr[cpath] = newNode;
			cpath++;
			
			copyCycle(cpath);
			cptr[cpath] = cptr[cpath]->pre;
			free(cptr[cpath]->next);
			cptr[cpath]->next = NULL;			
			
		}
		else if(visited[city[n].next[i]] == 0)	// does not exist
		{
			visited[city[n].next[i]] = 1;
			
			node *newNode = malloc(sizeof(node));
			strcpy(newNode->data, city[city[n].next[i]].name); 
			newNode->pre = cptr[cpath];
			cptr[cpath]->next = newNode;
			newNode->next = NULL;
			cptr[cpath] = newNode; 
			
			findCycle(city[n].next[i]);	
			
			cptr[cpath] = cptr[cpath]->pre;
			free(cptr[cpath]->next);
			cptr[cpath]->next = NULL;
			
			visited[city[n].next[i]] = 0;
		}
	}
}

void copyCycle(int n)
{
	chead[n] = malloc(sizeof(node));
	strcpy(chead[n]->data, sp);
	chead[n]->pre = NULL;
	chead[n]->next = NULL;
	
	node *p, *tp;
	p = chead[n];
	tp = chead[n-1]->next;
	
	while(tp != NULL)
	{
		node* newNode = malloc(sizeof(node));
		strcpy(newNode->data, tp->data);
		newNode->pre = p;
		p->next = newNode;
		newNode->next = NULL;
		p = newNode;
		tp = tp->next;
	}
	cptr[n] = p;
}

void save()			
{
	node *p;
	for(int i = 0; i < path; i++)
	{
		p = head[i];
		while(p != ptr[i])			// except the end point
		{
			arrive[map(p->data)] = 1;
			p = p->next;
		}
	}
}

void compare()
{
	node *p;
	int count = 0;
	for(int i = 0; i < cpath; i++)
	{
		int index = 0;
		p = chead[i];
		
		while(p != NULL)					// find the start of cycle
		{
			if(strcmp(p->data, cptr[i]->data) == 0 && p!=cptr[i] )
				break;
			p = p->next;
		}
		
		while(p != NULL)					// check whether there is a path to the end point
		{
			if(arrive[map(p->data)] == 1)
			{
				index = 1;
				break;
			}
			p = p->next;
		}
		
		if(index == 1)
		{
			p = chead[i];
			count++;
			while(p != NULL)
			{
				if(p != cptr[i])
					printf("%s,", p->data);
				else
					printf("%s\n", p->data);
				p = p->next;
			}
		}
	}
	if(count == 0)
		printf("NULL\n");
}
