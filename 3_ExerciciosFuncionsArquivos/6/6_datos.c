#include <stdio.h>
#include <stdlib.h>
#include "6_datos.h"

#define LIST_MAX 64

inline void
switch_values(int* a, int* b) {

    int aux = *a;
    *a = *b;
    *b = aux;

}

int
list_max(int* list, size_t size) {

    int value = list[0];

    for (int i = 1; i < size; i++) {
        if (list[i] > value) {
            value = list[i];
        }
    }

    return value;

}

int
list_min(int* list, size_t size) {

    int value = list[0];

    for (int i = 1; i < size; i++) {
        if (list[i] < value) {
            value = list[i];
        }
    }

    return value;

}

int
list_mode(int* list, size_t size) {

    list_order(list, size);

    int mode = 0;
    int max_count = 0;

    for (size_t i = 0; i < size; i++) {

        int count = 0;

        for (size_t j = i + 1; j < size; j++) {

            if (list[i] == list[j]) count++;
            else break;

        }

        if (count >= max_count) {
            max_count = count;
            mode = list[i];
        }

        i += count;

    }

    return mode;

}

float
list_average(int* list, size_t size) {

    int sum = 0;

    for (size_t i = 0; i < size; i++) {
        sum += list[i];
    }

    return (float) (sum / size);
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

void
list_read_file(int* list, size_t* size) {

    FILE* fin = fopen("./5_datos.txt", "r");

    if (fin == NULL) {
        printf("Error abrindo o arquivo\n");
        exit(1);
    }

    while (1) {

        char buff[256] = { 0 };

        if (fscanf(fin, "%s", buff) != 1) break;

        list[(*size)++] = atoi(buff);

    }

    fclose(fin);

}

void
list_print_file(int* list, size_t size) {

    FILE* fout = fopen("./6_datos_out.txt", "w");

    fprintf(fout, "Media: %f\nModa: %d\nMaximo: %d\nMinimo: %d\n",
        list_average(list, size),
        list_mode(list, size),
        list_max(list, size),
        list_min(list, size)
    );

    fclose(fout);

    return;
}

int
main(int argc, char** argv) {

    int list[LIST_MAX] = { 0 };
    size_t size = 0;

    list_read_file(list, &size);

    if (!size) {
        printf("Non existe ningunha lista\n");
        return 1;
    }

    printf("Lista: ");

    for (size_t i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }

    printf("\n");

    list_print_file(list, size);

    return 0;
}
