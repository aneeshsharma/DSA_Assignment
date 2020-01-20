/* Program to input a Binary Tree in parantheses format and print size of the largest BST
 * Author   -   Anish Sharma
 * Date     -   19/01/2020
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void insert(Node** root, Node* element) {
    if (*root == NULL) {
        *root = element;
        return;
    }

    Node* x = *root;
    Node* y = x;

    while (x != NULL) {
        y = x;
        if (element->data < x->data) x = x->left;
        else x = x->right;
    }

    if (element->data < y->data) y->left = element;
    else y->right = element;
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

Node* buildTree(char* cmd, int start, int end) {
    int num = 0;

    if (start >= end) return NULL;

    Node* root = NULL;
    int i = 0;

    for (i=start; i <= end && cmd[i] != '('; i++);
    if (i == end) return NULL;
    i++;
    int flag = 0;
    int sign = 1;
    while (cmd[i] != '(' && cmd[i] != ')') {
        if (cmd[i] == '-') {
            sign = -1;
        }
        if (isdigit(cmd[i])) {
            flag = 1;
            num *= 10;
            num += (int) cmd[i] - '0';
        }
        
        i++;

        if (i >= end)
            return NULL;
    }

    num *= sign;

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

int max(int a, int b) { return (a > b) ? a : b; }

int min(int a, int b) { return (a < b) ? a : b; }


int findMin(Node* root) {
    if (root == NULL) return INT_MAX;
    return min(root->data, min(findMin(root->left), findMin(root->right)));
}

int findMax(Node* root) {
    if (root == NULL) return INT_MIN;
    return max(root->data, max(findMax(root->left), findMax(root->right)));
}

int maxSubBST(Node* root) {
    if (!root) return 0;
    int left = 0, right = 0;
    int flag = 0;

    if (root->left) {
        if (findMax(root->left) > root->data)
            flag=1;
        left = maxSubBST(root->left);
    }

    if (root->right) {
        if (findMin(root->right) < root->data)
            flag=1;
        right = maxSubBST(root->right);
    }

    if (!flag)
        return left + right + 1;

    return max(left, right);
}

void main() {
    Node* root = NULL;

    char cmd[500];
    scanf("%[^\n]s", cmd);

    root = buildTree(cmd, 0, 500);

    int num = maxSubBST(root);
    printf("%d\n", num);
}
