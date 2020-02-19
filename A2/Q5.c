/* Program to find if its possible to construct a word out of a given string
 * Author   -   Anish Sharma
 * Date     -   10-02-2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Student {
    int key;
    int recorded;
} Student;

typedef Student* Students;

int isPrime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;

    int len = (int) sqrt(n) + 1;
    for (int i = 2; i < len; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int primeBelow(int x) {
    if (x <= 1 || isPrime(x)) return x;
    return primeBelow(x - 1);
}

int hash(int k, int m) { return k % m; }

int hash2(int k, int m) {
    int R = primeBelow(m - 1);
    return R - (m % R);
}

int hashA(int k, int i, int m, Students students) {
    int index = (hash(k, m) + i) % m;
    return index;
}

int hashB(int k, int i, int m, int c1, int c2, Students students) {
    int index = (hash(k, m) + c1 * i + c2 * i * i) % m;
    return index;
}

int hashC(int k, int i, int m, Students students) {
    int index = (hash(k, m) + i * hash2(k, m)) % m;
    return index;
}

Student newStudent(int key) {
    Student std = {key, 0};
    return std;
}

int insert(int key, Students students, int m, char function, int c1, int c2) {
    int h = -1, i;
    for (i = 0; i < m; i++) {
        switch (function) {
            case 'a':
                h = hashA(key, i, m, students);
                break;
            case 'b':
                h = hashB(key, i, m, c1, c2, students);
                break;
            case 'c':
                h = hashC(key, i, m, students);
                break;
        }
        if (h == -1)
            return -1;
        if (!students[h].recorded)
            break;
    }
    #ifdef DEBUG
        printf("Insert %d at %d | iterations : %d\n", key, h, i);
    #endif
    if (h == -1)
        return -1;
    students[h].key = key;
    students[h].recorded = 1;
}

int search(int key, Students students, int m, char function, int c1, int c2) {
    int h = -1;
    for (int i = 0; i < m; i++) {
        switch (function) {
            case 'a':
                h = hashA(key, i, m, students);
                break;
            case 'b':
                h = hashB(key, i, m, c1, c2, students);
                break;
            case 'c':
                h = hashC(key, i, m, students);
                break;
        }
        if (h == -1)
            return 0;
        if (students[h].recorded && students[h].key == key) { 
            #ifdef DEBUG
                printf("Found %d at %d\n", key, h);
            #endif
            return 1;
        }
    }
    return 0;
}

int delete(int key, Students students, int m, char function, int c1, int c2) {
    int h = -1;
    for (int i = 0; i < m; i++) {
        switch (function) {
            case 'a':
                h = hashA(key, i, m, students);
                break;
            case 'b':
                h = hashB(key, i, m, c1, c2, students);
                break;
            case 'c':
                h = hashC(key, i, m, students);
                break;
        }
        if (h == -1)
            return 0;
        if (students[h].key == key) {
            #ifdef DEBUG
                printf("Delete %d at %d\n", key, h);
            #endif
            students[h].recorded = 0;
            return 1;
        }
    }
    return 0;
}

void printStudents(Students std, int m) {
    for (int i = 0; i < m; i++) {
        printf("%d (", i);
        if (std[i].recorded)
            printf("%d", std[i].key);
        printf(")\n");
    }
} 

void main() {
    char choice, func;
    int m;
    int c1 = 0, c2 = 0;
    int num;

    scanf("%c %d", &func, &m);
    if (func == 'b') {
        scanf("%d %d", &c1, &c2);
    }
    
    Students std = calloc(m, sizeof(Student));
    
    int exit = 0;
    while (!exit) {
        scanf("%*c%c", &choice);

        switch (choice) {
            case 'i':
                scanf("%d", &num);
                insert(num, std, m, func, c1, c2);
                break;
            case 's':
                scanf("%d", &num);
                if (search(num, std, m, func, c1, c2))
                    printf("1\n");
                else
                    printf("-1\n");
                break;
            case 'd':
                scanf("%d", &num);
                delete(num, std, m, func, c1, c2);
                break;
            case 'p':
                printStudents(std, m);
                break;
            case 't':
                return;
        }
    }

    printStudents(std, m);
}