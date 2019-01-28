/*	 
 *  Title: Huffman coding for text files
 *  Idea: 1) build a huffman tree from input characters
 *        2) traverse the huffman tree and assign codes to characters
 *  Date: Dec, 2018
 */
 
#include<stdio.h>
#include<stdlib.h>
#define MAX 130

typedef struct node
{
	char data;
	int freq;
	int en;             // encoding size
	int arr[10];		// encoding table
	struct node *next, *left, *right;
}node;

typedef struct heap		// use min heap to implement priority queue
{
	int capacity;
	int size;
	struct node** arr;
}heap;

char data[MAX];
int freq[MAX];
int count = 0;
int sum = 0;			// total bits after compression
int index = 0;
int sz = 0;
node *head;

node* newNode(char data, int freq)			// utility function to create a new node
{
	node *n = malloc(sizeof(node));
	n->data = data;
	n->freq = freq;
	n->left = n->right = NULL;
	return n;
}

heap* newHeap(int capacity)					// utility function to create a new heap
{
	heap *h = malloc(sizeof(heap));
	h->capacity = capacity;
	h->size = 0;							// size is equal to 0 at the initial state
	h->arr = malloc(sizeof(node) * h->capacity);		// create space to accommodate nodes
	return h;
}

void swap(node **a, node **b)	// use the address to swap two nodes
{
	node *t = *a;
	*a = *b;
	*b = t;
}

void heapify(heap *h, int i)     // to modify the heap 
{
	int smallest = i;		
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	
	if(left < h->size && h->arr[left]->freq < h->arr[smallest]->freq)	// compare to the left child fist
		smallest = left;
	if(right < h->size && h->arr[right]->freq < h->arr[smallest]->freq)	 // then compare to the right child
		smallest = right;
	if(smallest != i)			// need to swap
	{
		swap(&h->arr[smallest], &h->arr[i]);
		heapify(h, smallest);		// heapify recursively
	}
}

int done(heap *h)		// return whether size of heap is equal to 1 or not
{
	return (h->size == 1);		
}

node* pop(heap *h)		// remove the smallest element (root) in the min heap 
{
	node *n = h->arr[0];				
	h->arr[0] = h->arr[h->size-1];		// use the leaf to replace the root
	h->size--;
	heapify(h, 0);		// modify the min heap
	return n;
}

void push(heap *h, node *n)
{
	h->size++;
	int i = h->size-1;
	while(i && n->freq < h->arr[(i-1)/2]->freq)		// check from down to up
	{
		h->arr[i] = h->arr[(i-1)/2];
		i = (i-1) / 2;
	}
	h->arr[i] = n;
}

void readFile(char ch)
{
	int i;
	for(i = 0; i < count; i++)
	{
		if(data[i] == ch)
		{
			freq[i] += 1;
			return;
		}
	}
	data[i] = ch;
	freq[i] = 1;
	count += 1;
}

int isLeaf(node *n)			// check if node is leaf (have no children)
{
	return (!(n->left) && !(n->right));
}

void create(node *n)		// create a linked list for nodes which contain input characters
{
	node *tmp, *ptr;
	ptr = malloc(sizeof(node));
	ptr->data = n->data;
	ptr->en = n->en;
	for(int i = 0; i < n->en; i++)
		ptr->arr[i] = n->arr[i];
	ptr->next = NULL;
	
	tmp = head;
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = ptr;
}

void encode(node *n, int list[], int i)   // assign 0 or 1 to left child and right child
{
	if(n->left)
	{
		list[i] = 0;
		encode(n->left, list, i + 1);
	}
	if(n->right)
	{
		list[i] = 1;
		encode(n->right, list, i + 1);
	}
	if(isLeaf(n))		// input character
	{
//		printf("[%c]\n", n->data);
		n->en = i;
		sum += n->en * n->freq;
		
		for(int i = 0; i < n->en; i++)
			n->arr[i] = list[i];		// encoding table
			
		if(index == 0)
		{
			head = malloc(sizeof(node));
			head->data = n->data;
			head->en = n->en;
			for(int i = 0; i < n->en; i++)
				head->arr[i] = n->arr[i];
			head->next = NULL;
			index++;
		}
		else
			create(n);	
	}
}

node* search(char data)
{
	node *n;
	n = head;
	while(n != NULL)
	{
		if(n->data == data)
			return n;
		n = n->next;
	}
}

void writeBit(int b, FILE *fw)		// maintain buffer, if it is full, write into file
{
	static unsigned char buffer = 0;
	buffer = buffer << 1;
	buffer += b;			   
	sz++;
	if(sz == 8)			// write into file
	{
		fwrite(&buffer, sizeof(char), 1, fw);
		buffer = 0;		// reset buffer
		sz = 0;
	}
}

void writeFile(node *p)
{
	FILE *fp, *fw;
	fp = fopen("input1.txt", "r");
	fw = fopen("output.txt", "wb");
	
	char ch;							
	while((ch = fgetc(fp)) != EOF)		 
	{
		node *n;
		n = search(ch);					// search input character in linked list
		for(int i = 0; i < n->en; i++)
			writeBit(n->arr[i], fw);
	}
	if(sz != 0)
		for(int i = sz; i < 8; i++)			// if the size is less than 8, add 0 
			writeBit(0, fw);
	
	fclose(fw);
	fclose(fp);
}

void inorder(node *p)
{
	if(p == NULL)
		return;
	inorder(p->left);
	printf("%c\n", p->data);
	inorder(p->right);
}

int main(void)
{
	FILE *fp;
	fp = fopen("input1.txt", "r");
	char ch;
	
	while((ch = fgetc(fp)) != EOF)			// read file
		readFile(ch);
	fclose(fp);
	
//	for(int i = 0; i < count; i++)
//	{
//		printf("!!!!%c %d\n", data[i], freq[i]);
//	}

	int freqs = 0;
	for(int i = 0; i < count; i++)
		freqs += freq[i];
	printf("file size before compression: %dbytes\n", freqs);
	
	heap* minHeap = newHeap(MAX);		
	for(int i = 0; i < count; i++)
	{
		node* n = newNode(data[i], freq[i]);
		push(minHeap, n);
//		printf("push: %c %d\n", minHeap->arr[i]->data, minHeap->arr[i]->freq);
	}
//	for(int i = 0; i < minHeap->size; i++)
//	{
//		printf("push: %c %d\n", minHeap->arr[i]->data, minHeap->arr[i]->freq);
//	}
	
	node *p;
	while(!done(minHeap))			    	// build a Huffman tree
	{
		node* m = pop(minHeap);
		node* n = pop(minHeap);
//		printf("(m, n) = %c %c\n", m->data, n->data);
		p = newNode('!', m->freq + n->freq);
		p->left = m;
		p->right = n;
		push(minHeap, p);
	}
//	inorder(p);
	int list[MAX], top = 0;				// traverse Huffman tree and create Huffman code
	encode(p, list, top);
	writeFile(p);
//	printf("file size after compression: %dbytes\n", (sum+7)/8);
	
//	node *t;
//	t = head;
//	while(t)
//	{
//		printf("%c ", t->data);
//		for(int i = 0; i < t->en; i++)
//		{
//			printf("%d", t->arr[i]);
//		}
//		printf("\n");
//		t = t->next;
//	}

	return 0;
}
