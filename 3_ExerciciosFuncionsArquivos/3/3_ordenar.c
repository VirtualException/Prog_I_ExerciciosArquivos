#include <stdio.h>
#include "3_ordenar.h"

#define LIST_N 8

inline void
switch_values(int* a, int* b) {

    int aux = *a;
    *a = *b;
    *b = aux;

}

int
list_order_onepass(int* list, size_t size) {

    for (size_t i = 0; i < size - 1; i++) {

        if (list[i] > list[i + 1]) {
            switch_values(&list[i], &list[i + 1]);
            return 1;
        }

    }

    return 0;
}

void
list_order(int* list, size_t size) {

    while (list_order_onepass(list, size));

}

int
main(int argc, char** argv) {

    int list[LIST_N] = { -1, 2, 4, 1, 3, 10, 9, 1 };

    printf("Lista: ");

    for (size_t i = 0; i < LIST_N; i++) {
        printf("%d ", list[i]);
    }

    printf("\n");

    list_order(list, LIST_N);

    printf("Lista ordenada: ");

    for (size_t i = 0; i < LIST_N; i++) {
        printf("%d ", list[i]);
    }

    printf("\n");

    return 0;
}
