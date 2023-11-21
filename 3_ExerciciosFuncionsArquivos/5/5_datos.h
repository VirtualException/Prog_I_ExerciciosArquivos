#ifndef _5_DATOS_H
#define _5_DATOS_H

#include <stddef.h>

void    switch_values(int* a, int* b);

int     list_max(int* list, size_t size);
int     list_min(int* list, size_t size);
int     list_mode(int* list, size_t size);
float   list_average(int* list, size_t size);
int     list_order_onepass(int* list, size_t size);
void    list_order(int* list, size_t size);
void    list_read_file(int* list, size_t* size);

#endif
