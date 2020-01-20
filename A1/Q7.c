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

int findMaxSubBST(Node* root, int* maxChild, int* minChild, int* valid) {
    if (!root) return 0;
    int left = 0, right = 0;
    int flag = 0;

    if (!root->left && !root->right) {
        *maxChild = root->data;
        *minChild = root->data;
        *valid = 1;
        return 1;
    }

    int leftMax = INT_MIN;
    int rightMax = INT_MIN;
    int leftMin = INT_MAX;
    int rightMin = INT_MAX;

    int leftValid = 1, rightValid = 1;

    if (root->left) {
        left = findMaxSubBST(root->left, &leftMax, &leftMin, &leftValid);
        if (leftMax > root->data)
            flag=1;
    }

    if (root->right) {
        right = findMaxSubBST(root->right, &rightMax, &rightMin, &rightValid);
        if (rightMin < root->data)
            flag=1;
    }

    if (!leftValid || !rightValid)
        flag = 1;

    *maxChild = max(root->data, max(leftMax, rightMax));
    *minChild = min(root->data, min(leftMin, rightMin));

    if (flag) {
        *valid = 0;
    }

    if (!flag) {
        return left + right + 1;
    }
    return max(left, right);
}

int maxSubBST(Node* root) {
    int max, min, valid;

    return findMaxSubBST(root, &max, &min, &valid);
}

void main() {
    Node* root = NULL;

    char cmd[500];
    scanf("%[^\n]s", cmd);

    root = buildTree(cmd, 0, 500);
    int num = maxSubBST(root);
    
    printf("%d\n", num);
}
