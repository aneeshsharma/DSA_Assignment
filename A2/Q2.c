#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* newNode(int value) {
    Node* new = (Node*) malloc(sizeof(Node));
    new->data = value;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Node* buildTree(char* cmd, int start, int end) {
    int num = 0;

    if (start >= end) return NULL;

    Node* root = NULL;
    int i = 0;

    for (i=start; i <= end && cmd[i] != '('; i++);
    if (i == end) return NULL;
    i++;

    int flag = 0;
    while (cmd[i] != '(' && cmd[i] != ')') {
        if (isdigit(cmd[i])) {
            flag = 1;
            num *= 10;
            num += (int) cmd[i] - '0';
        }
        
        i++;

        if (i >= end)
            return NULL;
    }

    if (!flag) return NULL;

    root = newNode(num);

    if (cmd[i] == ')') {
        return root;
    }

    int startNew = i;
    int count = 0;
    for (; i <= end; i++) {
        if (cmd[i] == '(') count++;
        else if (cmd[i] == ')') count--;

        if (count <= 0) break;
    }

    root->left = buildTree(cmd, startNew, i);
    i++;
    count = 0;

    for (; i <= end && cmd[i] != '('; i++);
    if (i == end) return NULL;

    startNew = i;

    for (; i <= end; i++) {
        if (cmd[i] == '(') count++;
        else if (cmd[i] == ')') count--;

        if (count <= 0) break;
    }

    root->right = buildTree(cmd, startNew, i);

    return root;
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

int isBST(Node* tree, int max, int min)
{
	if (tree == NULL)
		return 1;
	if (tree->data < min || tree->data > max)
		return 0;
	return isBST(tree->right, max, tree->data) && isBST(tree->left, tree->data, min);
}

int isAVL(Node* tree)
{
    if (!isBST(tree, INT_MAX, INT_MIN))
        return 0;

	if (tree != NULL)
	{
		int bal = getBalance(tree);
		if (bal < 0)
			bal *= -1;
		if (bal > 1)
			return 0;
		return isAVL(tree->left) && isAVL(tree->right);
	}
	else
		return 1;

}

void main() {
    char input[500];
    scanf("%[^\n]s", input);
    Node* tree = buildTree(input, 0, strlen(input) - 1);

    if (isAVL(tree))
        printf("1\n");
    else
        printf("0\n");
}