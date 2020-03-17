/* Program to check whether a Tree is a Valid Red Black Tree
 * Author   -   Anish Sharma
 * Date     -   09-02-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    int data;
    char color;
    struct Node *left, *right;
    int blackHeight;
} Node;

Node* newNode(int data, char color) {
    Node* node = (Node*) malloc(sizeof(Node));

    node->data = data;
    node->color = color;
    node->blackHeight = 0;
    node->left = node->right = NULL;
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
    while (cmd[i] != 'R' && cmd[i] != 'B' && cmd[i] != ')') {
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

    char color = cmd[i];

    for (; i <= end && cmd[i] != '(' && cmd[i] != ')'; i++);
    if (i == end) return NULL;

    root = newNode(num, color);

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

int isRedBlack(Node* root) {
    if (root == NULL)
        return 1;
    
    if (root->color != 'R' && root->color != 'B')
        return 0;
    
    if (root->color == 'R')
        if ((root->left && root->left->color == 'R') || (root->right && root->right->color == 'R'))
            return 0;
    
    if (root->blackHeight == -1)
        return 0;
    
    int left = isRedBlack(root->left);
    int right = isRedBlack(root->right);

    return left && right;
}

void setBlackHeight(Node* root) {
    if (root == NULL)
        return;
    
    if (root->left == NULL && root->right == NULL) {
        if (root->color == 'B')
            root->blackHeight = 1;
        else
            root->blackHeight = 0;
        return;
    }
    
    int left = 0, right = 0;

    if (root->left != NULL) {
        setBlackHeight(root->left);
        left = root->left->blackHeight;
    }

    if (root->right != NULL) {
        setBlackHeight(root->right);
        right = root->right->blackHeight;
    }

    if (left == -1 || right == -1) {
        root->blackHeight = -1;
        return;
    }
    
    if (left != right) {
        root->blackHeight = -1;
        return;
    }

    if (root->color == 'B')
        root->blackHeight = left + 1;
    else
        root->blackHeight = left;
}

void printTree(Node* root) {
    printf("( ");
    if (root == NULL) {
        printf(") ");
        return;
    }
    printf("%d %c ", root->data, root->color);
    printTree(root->left);
    printTree(root->right);
    printf(") ");
}

void main() {
    char in[5000];
    scanf("%[^\n]s", in);

    Node* root = buildTree(in, 0, strlen(in));

    setBlackHeight(root);
    printf("%d\n", isRedBlack(root));
}