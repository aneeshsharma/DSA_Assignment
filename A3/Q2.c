/* Program to insert elements into a Red-Black tree
 * Author   -   Anish Sharma
 * Date     -   17-03-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum DIRECTION { LEFT, RIGHT, UNI };

typedef struct Node {
    int data;
    char color;
    struct Node *left, *right, *parent;
    int blackHeight;
} Node;

Node* newChild(Node* parent, int dir, int data, char color) {
    Node* node = (Node*) malloc(sizeof(Node));

    node->data = data;
    node->color = color;
    node->blackHeight = 0;
    node->left = node->right;
    if (dir == LEFT) {
        parent->left = node;
    } else if (dir == RIGHT) {
        parent->right = node;
    } else {
        return node;
    }
    node->parent = parent;
}

Node* newNode(int data, char color) {
    newChild(NULL, UNI, data, color);
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

void rotateLeft(Node **root, Node *node) 
{ 
    Node *node_right = node->right; 
  
    node->right = node_right->left; 
  
    if (node->right != NULL) 
        node->right->parent = node;
  
    node_right->parent = node->parent; 
  
    if (node->parent == NULL) 
        *root = node_right;
    else if (node == node->parent->left) 
        node->parent->left = node_right; 
    else
        node->parent->right = node_right; 
  
    node_right->left = node; 
    node->parent = node_right; 
}

void rotateRight(Node **root, Node *node) 
{ 
    Node *node_left = node->left; 
  
    node->left = node_left->right; 
  
    if (node->left != NULL) 
        node->left->parent = node; 
  
    node_left->parent = node->parent;
  
    if (node->parent == NULL) 
        *root = node_left; 
    else if (node == node->parent->left) 
        node->parent->left = node_left; 
    else
        node->parent->right = node_left; 
  
    node_left->right = node; 
    node->parent = node_left; 
}

Node* BSTInsert(Node* root, Node* node) {
    if (root == NULL) {
        return node;
    }

    if (node->data < root->data) {
        root->left = BSTInsert(root->left, node);
        root->left->parent = root;
    } else if (node->data > root->data) {
        root->right = BSTInsert(root->right, node);
        root->right->parent = root;
    }

    return root;
}

void fixTree(Node **root, Node *node) 
{ 
    Node *parent_node = NULL;
    Node *grand_parent_node = NULL;
  
    while ((node != *root) && (node->color != 'B') && (node->parent->color == 'R')) 
    { 
  
        parent_node = node->parent; 
        grand_parent_node = node->parent->parent; 
  
        /*  Case : A 
            Parent of node is left child of Grand-parent of node */
        if (parent_node == grand_parent_node->left) 
        { 
  
            Node *uncle_pt = grand_parent_node->right; 
  
            /* Case : 1 
               The uncle of node is also red 
               Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == 'R') 
            { 
                grand_parent_node->color = 'R'; 
                parent_node->color = 'B'; 
                uncle_pt->color = 'B'; 
                node = grand_parent_node; 
            } 
  
            else
            { 
                /* Case : 2 
                   node is right child of its parent 
                   Left-rotation required */
                if (node == parent_node->right) 
                { 
                    rotateLeft(root, parent_node); 
                    node = parent_node; 
                    parent_node = node->parent; 
                } 
  
                /* Case : 3 
                   node is left child of its parent 
                   Right-rotation required */
                rotateRight(root, grand_parent_node); 

                char tmp = parent_node->color;
                parent_node->color = grand_parent_node->color;
                grand_parent_node->color = tmp; 
                
                node = parent_node; 
            } 
        } 
  
        /* Case : B 
           Parent of node is right child of Grand-parent of node */
        else
        { 
            Node *uncle_pt = grand_parent_node->left; 
  
            /*  Case : 1 
                The uncle of node is also red 
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == 'R')) 
            { 
                grand_parent_node->color = 'R'; 
                parent_node->color = 'B'; 
                uncle_pt->color = 'B'; 
                node = grand_parent_node; 
            } 
            else
            { 
                /* Case : 2 
                   node is left child of its parent 
                   Right-rotation required */
                if (node == parent_node->left) 
                { 
                    rotateRight(root, parent_node); 
                    node = parent_node; 
                    parent_node = node->parent; 
                } 
  
                /* Case : 3 
                   node is right child of its parent 
                   Left-rotation required */
                rotateLeft(root, grand_parent_node); 

                char tmp = parent_node->color;
                parent_node->color = grand_parent_node->color;
                grand_parent_node->color = tmp; 

                node = parent_node; 
            } 
        } 
    } 
  
    (*root)->color = 'B'; 
}

void insert(Node **root, int data) 
{ 
    Node *node = newNode(data, 'R'); 
    *root = BSTInsert(*root, node);
    fixTree(root, node); 
} 

void printTree(Node* root) {
    printf("( ");
    if (root != NULL) {
        printf("%d %c ", root->data, root->color);
        printTree(root->left);
        printTree(root->right);
    }
    printf(") ");
}

void main() {
    int num;
    Node* root = NULL;

    while (1) {
        scanf("%d", &num);
        insert(&root, num);
        printTree(root);
        printf("\n");
    }
}