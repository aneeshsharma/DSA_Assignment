/* Program to input BST in preorder and print it in parantheses representation
 * Author   -   Anish Sharma
 * Date     -   19/01/2020
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void main() {
    Node* root = NULL;

    int num, size;
    scanf("%d", &size);

    for (int i = 0; i < size; i++) {
        scanf("%d", &num);
        insert(&root, newNode(num));
    }

    paren(root);
    printf("\n");
}
