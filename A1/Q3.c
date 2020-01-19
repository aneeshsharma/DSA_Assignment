/* Program to input a BST in parantheses format and mirror it
 * Author   -   Anish Sharma
 * Date     -   19/01/2020
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IS_DIGIT(x) ((x <= '9') && (x >= '0'))

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

Node* buildTree(char* cmd) {
    int num = 0;
    
    Node* root = NULL;
    int numStart = 0;

    while (*cmd != '\0') {
        if (isdigit(*cmd)) {
            numStart = 1;
            num *= 10;
            num += (int) *cmd - '0';
        } else {
            if (numStart) {
                insert(&root, newNode(num));
                num = 0;
                numStart = 0;
            }
        }
        cmd++;
    }
    return root;
}

void mirror(Node* root) {
    if (!root) return;
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
}

void main() {
    Node* root = NULL;

    char cmd[500];
    int num;
    scanf("%[^\n]s", cmd);

    root = buildTree(cmd);
    
    mirror(root);
    paren(root);
    printf("\n");
}
