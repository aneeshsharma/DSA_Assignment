#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Node
{
	struct Node* left;
	struct Node* right;
	int data;
} Node;


Node* newNode(int value) {
    Node* new = (Node*) malloc(sizeof(Node));
    new->data = value;
    new->left = NULL;
    new->right = NULL;
    return new;
}

void paren(Node* root) {
    printf("( ");
    if (root == NULL) {
        printf(") ");
        return;
    }
    printf("%d ", root->data);
    paren(root->left);
    paren(root->right);
    printf(") ");
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

Node* findMin(Node *tree)
{
	if (tree->left == NULL)
		return tree;
	else
		return findMin(tree->left);
}
Node* findMax(Node*tree)
{
	if (tree->right == NULL)
		return tree;
	else
		return findMax(tree->right);
}

Node* predecessor(Node *tree,int i)
{
	Node *x, *y = NULL;
	x = search (tree,i);
	if (x->left != NULL)
			return findMax(x->left);
	else
	{
			while (tree != NULL)
			{
					if (i < tree->data)
							tree = tree->left;
					else if (i > tree->data)
					{
							y = tree;
							tree = tree->right;
					}
					else if (i == tree->data)
					{
							return y;
					}
			}
	}

	return NULL;
}

Node* successor(Node *tree, int i)
{
	Node *x, *y = NULL;
	x = search(tree, i);
	if (x->right != NULL)
		return findMin(x->right);
	else 
	{
		while (tree != NULL)
		{
			if (i > tree->data)
				tree = tree->right;
			else if (i < tree->data)
			{
				y = tree;
				tree = tree->left;
			}
			else if (i == tree->data)
			{
				return y;
			}
		}
	}

	return NULL;
}

Node* delete(Node *tree, Node *z, int i)
{
	Node *temp, *temp2;
	//exit condition
	if (tree == NULL)
		return tree;

	else if (i < tree->data && tree != z)
	{
		tree->left = delete(tree->left, z, i);
	}
	else if (i > tree->data && tree != z)
	{
		tree->right = delete(tree->right, z, i);
	}
	else if (tree==z)
	{
		// no child
		if (tree->right == NULL && tree->left == NULL)
		{
			free(tree);
			return NULL;
		}
		//single child
		else if (tree->right == NULL)
		{
			temp = tree->left;
			free(tree);
			return temp;
		}
		else if (tree->left == NULL)
		{
			temp = tree->right;
			free(tree);
			return temp;
		}
		//two child
		temp2 = successor(tree, tree->data);
		tree->data = temp2->data;
		tree->right = delete(tree->right, z, temp2->data);
	}
	if (tree == NULL)
		return NULL;
	
	int delta = getBalance(tree);

	if (delta > 1 && getBalance(tree->left) >= 0)
		return rightRotate(tree);

	if (delta > 1 && getBalance(tree->left) < 0)
	{
		tree->left =  leftRotate(tree->left);
		return rightRotate(tree);
	}

	if (delta < -1 && getBalance(tree->right) <= 0)
		return leftRotate(tree);

	if (delta < -1 && getBalance(tree->right) > 0)
	{
		tree->right = rightRotate(tree->right);
		return leftRotate(tree);
	}

	return tree;
}

int main()
{
	char s[6];
	int i, k, delta;
	Node *tree, *foundNode;
	
	tree = NULL;
	
	while (1)
	{
		scanf("%s", s);

		if (strcmp("insr", s) == 0)
		{
			scanf("%d", &i);
			tree = insert(tree, i);
		}
		else if (strcmp("pbal", s) == 0)
		{
			scanf("%d", &k);
			foundNode = search(tree, k);
			if (foundNode == NULL)
				printf("FALSE\n");
			else
			{
				delta = getBalance(foundNode);
				printf("%d\n", delta);
			}
		}
		else if (strcmp("disp",s) == 0)
		{
			paren(tree);
			printf("\n");
		}
		else if (strcmp("srch",s) == 0)
		{
			scanf ("%d",&k);
			foundNode = search(tree, k);
			if (foundNode == NULL)
				printf("FALSE\n");
			else 
				printf("TRUE\n");
		}
		else if (strcmp("delt", s) == 0)
		{
			scanf("%d", &i);
			foundNode = search(tree, i);
			if (foundNode == NULL)
				printf("NULL\n");
			else
				tree = delete(tree, foundNode, i);
		}
		else 
			return 0;
	}
}
