/* Program to find if its possible to construct a word out of a given string
 * Author   -   Anish Sharma
 * Date     -   09-02-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOWED_CHARS 52

typedef struct Table {
    int* freq;
    int capacity;
} Table;

int hash(char c, int cap) {
    int i = 0;
    if (c >= 'a' && c <= 'z') {
        i = c - 'a';
    }
    else if (c >= 'A' && c <= 'Z') {
        i = c - 'A' + 26;
    }

    i = i % cap;
    return i;
}

Table* newTable(int cap) {
    Table* table = (Table*) malloc(sizeof(Table));
    table->freq = calloc(cap, sizeof(int));
    table->capacity = cap;
}

void delete(Table* table) {
    free(table->freq);
    free(table);
}

void increase(char c, Table* table) {
    int h = hash(c, ALLOWED_CHARS);
    table->freq[h] += 1;
}

int decrease(char c, Table* table) {
    int h = hash(c, ALLOWED_CHARS);
    if (table->freq[h] <= 0)
        return 0;
    table->freq[h] -= 1;
    return 1;
}

int find(char* word, int len, Table* table) {
    for (int i = 0; i < len; i++) {
        if (!decrease(word[i], table))
            return 0;
    }
    return 1;
}

void increaseSet(char* str, int len, Table* table) {
    for (int i = 0; i < len; i++)
        increase(str[i], table);
}

void printTable(Table* table) {
    for (int i = 0; i < table->capacity; i++) {
        if (table->freq[i] > 0)
            printf("%d -> %d\n", i, table->freq[i]);
    }
}

void main() {
    int sets=0;

    scanf("%d", &sets);

    for (int i = 0; i < sets; i++) {
        Table* table = newTable(ALLOWED_CHARS);

        char word[50];
        char set[200];
        scanf("%s", word);
        scanf("%s", set);

        increaseSet(set, strlen(set), table);
        if (find(word, strlen(word), table))
            printf("YES");
        else
            printf("NO");
        printf("\n");

        delete(table);
    }
}