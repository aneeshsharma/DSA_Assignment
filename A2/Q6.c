#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Node
{
	int count;
    int data;
	struct Node* left;
	struct Node* right;
} Node;


Node* newNode(int key)
{
    	Node* node = (Node*)malloc(sizeof(Node));
    	node->data = key;
        node->count = 0;
    	node->left = NULL;
    	node->right = NULL;
    	return node;
}

int max(int x, int y) { return (x > y) ? x : y; }

int height(Node* tree)
{
	int l,r;
	if (tree==NULL)
		return 0;
	else
	{
		l = height(tree->left);
		r = height(tree->right);
		return max(l + 1, r + 1);
	}
}

int getBalance(Node* z)
{
	if (z == NULL)
		return 0;
	else
		return height(z->left) - height(z->right);
}

Node* leftRotate(Node* tree)
{
	Node* y = tree->right; 
	Node* T2 = y->left;
	y->left = tree; 
	tree->right = T2; 
	return y;
}

Node* rightRotate(Node* tree)
{
	Node* x = tree->left; 
	Node* T2 = x->right; 
	x->right = tree; 
	tree->left = T2;
	return x;
}

Node* search(Node* tree, int k)
{
	if (tree == NULL)
		return NULL;
	if (tree->data == k)
		return tree;
	else if (k < tree->data)
		return search(tree->left, k);
	else
		return search(tree->right, k);
}

Node* insert(Node* node, int key)  
{  
	int delta;
	if (node == NULL)  
        	return newNode(key);  
  
	if (key < node->data)  
		node->left = insert(node->left, key);  
	else
		node->right = insert(node->right, key); 
	
	delta = getBalance(node);   
	
	if (delta > 1 && key < node->left->data)  
		return rightRotate(node);  

	if (delta < -1 && key > node->right->data)  
		return leftRotate(node);  
	
	if (delta > 1 && key > node->left->data)  
	{  
		node->left = leftRotate(node->left);  
		return rightRotate(node);  
	}
	
	if (delta < -1 && key < node->right->data)  
	{  
		node->right = rightRotate(node->right);  
		return leftRotate(node);  
	}
	
	return node;
}

void transform(Node* tree, int* array, int* x)
{
	if (tree != NULL)
	{
		transform(tree->left, array, x);

		for (int i = 0; i < tree->count; i++)
		{
			array[*x] = tree->data;
			*x += 1;
		}

		transform(tree->right,array,x);
	}
}

void sort(int* array, int size) {
    Node *tree ,*foundNode,*node;
    int flag = 0;

    tree = NULL;

    for (int i = 0; i < size; i++)
	{
		flag=0;
		node = tree;
		while (node != NULL)
		{
			if (array[i] == node->data)
			{
				node->count++;
				flag = 1;
				break;
			}
			else if (array[i] < node->data)
				node = node->left;
			else
				node = node->right;
		}

		if (!flag)
		{
			tree = insert(tree, array[i]);
			foundNode = search(tree, array[i]);
			foundNode->count = 1;
		}

	}
	int num = 0;
	transform(tree, array, &num);
}

void printArray(int* array, int size) {
    int i;
    for (i = 0; i < size - 1; i++)
	{
		printf("%d ", array[i]);
	}
	printf("%d\n", array[i]);
}

int main()
{
	int length;
	scanf ("%d",&length);

	int array[length];
	for (int i = 0; i < length; i++)
	{
		scanf("%d", &array[i]);
	}
	
	sort(array, length);
    printArray(array, length);
	return 0;
}