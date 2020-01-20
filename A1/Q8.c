/* Program to encode a given string with Huffman encoding using Binary Tree
 * Author   -   Anish Sharma
 * Date     -   19/01/2020
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define LEFT(i) (2*i)
#define RIGHT(i) (2*i + 1)
#define PARENT(i) (i/2)

#define CHAR_SET 127

typedef struct Code {
    char ch;
    int code;
    struct Code* next;
} Code;

typedef struct Node {
    int freq;
    char ch;
    struct Node *left, *right;
} Node;

typedef struct Queue {
    Node** queue;
    int size, capacity;
} Queue;

Code* newCode(char ch, int code) {
    Code* new = malloc(sizeof(Code));
    new->ch = ch;
    new->code = code;
    new->next = NULL;
    return new;
}

Node* newNode(char ch, int freq) {
    Node* new = (Node*) malloc(sizeof(Node));
    new->freq = freq;
    new->ch = ch;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Queue* newPriorityQueue(int size) {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->capacity = size;
    q->size = 0;
    q->queue = (Node**) calloc(q->capacity, sizeof(Node*));
    return q;
}

void deleteQueue(Queue* q) {
    free(q->queue);
    free(q);
}

void minHeapify(Queue* q, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int smallest = i;
    if (l < q->size && q->queue[l]->freq < q->queue[i]->freq)
        smallest = l;
    if (r < q->size && q->queue[r]->freq < q->queue[i]->freq)
        smallest = r;
    if (smallest != i) {
        Node* temp = q->queue[i];
        q->queue[i] = q->queue[smallest];
        q->queue[smallest] = temp;
        minHeapify(q, smallest);
    }
}

Node* dequeue(Queue* q) {
    if (q->size <= 0) return NULL;

    Node* min = q->queue[0];
    q->queue[0] = q->queue[q->size - 1];
    q->size--;
    minHeapify(q, 0);

    return min;
}

Node* enqueue(Queue* q, Node* new) {
    if (q->size >= q->capacity) return NULL;
    q->size++;

    q->queue[q->size - 1] = new;

    int i = q->size - 1;
    while (i > 0 && q->queue[PARENT(i)]->freq > q->queue[i]->freq) {
        Node* temp = q->queue[PARENT(i)];
        q->queue[PARENT(i)] = q->queue[i];
        q->queue[i] = temp;
        i = PARENT(i);
    }

    return new;
}

void printQueue(Queue* q) {
    Node* node;
    while ((node = dequeue(q)) != NULL) {
        printf("(%c, %d) | ", node->ch, node->freq);
    }
    printf("\n");
}

void paren(Node* root) {
    printf("( ");
    if (root == NULL) {
        printf(") ");
        return;
    }
    printf("[%c | %d]", root->ch, root->freq);
    paren(root->left);
    paren(root->right);
    printf(") ");
}

void push(Code** stack, Code* c) {
    c->next = *stack;
    *stack = c;
}

void generateCodes(Node* root, Code** codeVault, int code) {
    if (root->ch != 0) {
        Code* c = newCode(root->ch, code);
        push(codeVault, c);
        return;
    }
    generateCodes(root->left, codeVault, code*10 + 0);
    generateCodes(root->right, codeVault, code*10 + 1);
}

void printList(Code* root) {
    if (root == NULL) return;
    printf("[%c, %d] ", root->ch, root->code);
    printList(root->next);
}

int getCode(Code* codeVault, char ch) {
    if (codeVault == NULL) return -1;
    if (codeVault->ch == ch) return codeVault->code;
    return getCode(codeVault->next, ch);
}

Code* Find_huffman_Code(char* m) {
    int freq[CHAR_SET];
    Queue* q;

    q = newPriorityQueue(100);
    
    int len = strlen(m);

    for (char i = 0; i < CHAR_SET; i++) {
        freq[i] = 0;
    }

    for(int i=0; i < len; i++) {
        freq[m[i]]++;
    }

    for (char i = 0; i < CHAR_SET; i++) {
        if (freq[i] > 0) {
            Node* new = newNode(i, freq[i]);
            if (!enqueue(q, new)) {
                return 0;
            }
        }
    }
    
    while (q->size > 1) {
        Node* a = dequeue(q);
        Node* b = dequeue(q);
        Node* new = newNode(0, a->freq + b->freq);
        new->left = a;
        new->right = b;
        enqueue(q, new);
    }

    Node* root = dequeue(q);

    Code* codeVault = NULL;

    generateCodes(root, &codeVault, 0);

    deleteQueue(q);

    return codeVault;
}

int getNumLength(int num) {
    if (num == 0) return 1;
    int count = 0;
    while (num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

void print_Code_Length(char* m) {
    Code* vault = Find_huffman_Code(m);
    int len = strlen(m);
    int code;
    int codeLength = 0;
    for (int i = 0; i < len; i++) {
        code = getCode(vault, m[i]);
        codeLength += getNumLength(code);
    }
    printf("%d\n", codeLength);
}

void main() {
    char input[100];

    do {
        scanf("%s", input);
        print_Code_Length(input);
    } while(strlen(input) > 0);
}
