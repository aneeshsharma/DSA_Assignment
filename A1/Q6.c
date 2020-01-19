/* Program to input a BST in parantheses format and print in each nodes sum format
 * Author   -   Anish Sharma
 * Date     -   19/01/2020
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    int data, sum;
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
    printf("%d ", root->sum);
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

int sum(Node* root) {
    if (root == NULL) return 0;
    root->sum = sum(root->left) + sum(root->right) + root->data;
    return root->sum;
}

void main() {
    Node* root = NULL;

    char cmd[500];
    scanf("%[^\n]s", cmd);

    root = buildTree(cmd, 0, 500);

    sum(root);

    paren(root);
    printf("\n");
}
