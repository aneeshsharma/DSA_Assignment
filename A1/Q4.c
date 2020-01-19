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

Node* search(Node* root, int data) {
    if (root == NULL) return NULL;

    if (root->data == data) return root;
    else if (root->data < data) return search(root->right, data);
    else return search(root->left, data);
}

int level(Node* root, int data) {
    Node* x = root;
    for (int level = 0; x != NULL; level++) {
        if (x->data == data) return level;
        else if (x->data > data) x = x->left;
        else x = x->right;
    }
    return -1;
}

Node* findMaxNode(Node* root) {
    if (root == NULL) return NULL;
    if (root->right == NULL) return root;
    return findMaxNode(root->right);
}

Node* findMinNode(Node* root) {
    if (root == NULL) return NULL;
    if (root->left == NULL) return root;
    return findMinNode(root->left);
}

int findMin(Node* root) {
    if (root == NULL) return -1;
    if (root->left == NULL) return root->data;
    return findMin(root->left);
}

int findMax(Node* root) {
    if (root == NULL) return -1;
    if (root->right == NULL) return root->data;
    return findMax(root->right);
}

Node* predecessor(Node* root, Node* node) {
    if (node == NULL || root == NULL) return NULL;
    if (node->left != NULL) return findMaxNode(node->left);
    Node* x = root;
    Node* y = NULL;
    Node* max = (Node*) -1;
    while (x != NULL) {
        y = x;

        if (node->data > x->data) {
            if (!max) max = x;
            if (max->data < x->data) {
                max = x;
            }
            x = x->right;
        }
        else if (node->data < x->data) {
            x = x->left;
        }
        else {
            return max;
        }
    }
    return max;
}

Node* successor(Node* root, Node* node) {
    if (node == NULL || root == NULL) return NULL;
    if (node->right != NULL) return findMinNode(node->right);
    Node* x = root;
    Node* y = NULL;
    Node* min = (Node*) -1;
    while (x != NULL) {
        y = x;

        if (node->data < x->data) {
            if (!min) min = x;
            if (min->data > x->data) {
                min = x;
            }
            x = x->left;
        }
        else if (node->data > x->data) {
            x = x->right;
        }
        else {
            return min;
        }
    }
    return min;
}

Node* getParent(Node* root, Node* node) {
    Node* prev = NULL;
    while (root != NULL) {
        if (node == root) return prev;
        prev = root;
        if (node->data < root->data) root = root->left;
        else root = root->right;
    }
    return NULL;
}

void delete(Node** root, int data) {
    Node* node = search(*root, data);
    if (node == NULL) return;
    if (!node->left && !node->right) {
        Node* p = getParent(*root, node);
        if (p) {
            if (p->left == node)
                p->left = NULL;
            else
                p->right = NULL;
        }
        else {
            *root = NULL;
        }
    } else if (!node->left || !node->right) {
        Node* p = getParent(*root, node);
        Node* new = node->left ? node->left : node->right;
        if (p) {
            if (p->left == node)
                p->left = new;
            else
                p->right = new;
        }
        else {
            *root = new;    
        }
    } else {
        Node* suc = successor(*root, node);
        if (!suc) return;
        Node* p = getParent(*root, suc);
        if (!p) return;
        Node* delP = getParent(*root, node);

        if (suc == node->right)
            suc->right = NULL;
        else
            suc->right = node->right;
        suc->left = node->left;

        if (delP != NULL) {
            if (delP->left == node)
                delP->left = suc;
            else
                delP->right = suc;
        } else {
            *root = suc;
        }

        if (p->left == suc) p->left = NULL;
        else p->right = NULL;
    }
    free(node);
}

void inorder(Node* node) {
    if (node == NULL)
        return;
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

void preorder(Node* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    preorder(node->left);
    preorder(node->right);
}

void postorder(Node* node) {
    if (node == NULL) return;
    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->data);
}

void paren(Node* root) {
    printf("(");
    if (root == NULL) {
        printf(")");
        return;
    }
    printf("%d", root->data);
    paren(root->left);
    paren(root->right);
    printf(")");
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
