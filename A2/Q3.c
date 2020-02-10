/* Program to group words according to their lengths in a hash table
 * Author   -   Anish Sharma
 * Date     -   09-02-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

typedef struct Table {
    Node** table;
    int capacity;
} Table;

Node* newNode(char* data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void push(Node** head, char* data) {
    Node* new = newNode(data);
    if (*head == NULL) {
        *head = new;
    } else {
        Node* it = *head;
        while (it->next != NULL) it = it->next;
        it->next = new;
    }
}

Table* newTable(int cap) {
    Table* table = (Table*) malloc(sizeof(Table));
    table->capacity = cap;
    table->table = (Node**) calloc(cap, sizeof(Node*));
    return table;
}

int isIn(Node* list, char* data) {
    if (!list) return 0;
    if (strcmp(list->data, data) == 0) return 1;
    return isIn(list->next, data);
}

void insertData(Table* table, char* data) {
    int len = strlen(data);
    int index = len % table->capacity;
    Node** list = table->table + index;
    if (isIn(*list, data)) return;
    push(table->table + index, data);
}

char* getNext(char* input, int* i, int len) {
    int j = 0;

    for (; *i < len && input[*i] == ' '; (*i)++);

    if (*i >= len) return 0;

    char* buf = malloc(30 * sizeof(char));

    while (*i < len && input[*i] != ' ') {
        if (isalpha(input[*i])) {
            buf[j] = input[*i];
            j++;
        }
        (*i)++;
    }
    if (j == 0)
        return NULL;
    buf[j] = '\0';
    return buf;
}

void fetchData(Table* table, char* input) {
    int i=0;
    int len = strlen(input);
    char* buf;
    while (buf = getNext(input, &i, len)) {
        insertData(table, buf);
    }
}

void printList(Node* list) {
    if (list == NULL)
        return;
    printf("%s ", list->data);
    printList(list->next);
}

void printTable(Table* table) {
    for (int i = 0; i < table->capacity; i++){
        if (table->table[i] == NULL)
            printf("NULL");
        printList(table->table[i]);
        printf("\n");
    }
}

void main() {
    int cap;
    scanf("%d%*c", &cap);
    Table* table = newTable(cap);
    char* input = malloc(200 * sizeof(char));
    scanf("%[^\n]s%*c", input);
    fetchData(table, input);
    printTable(table);
}

