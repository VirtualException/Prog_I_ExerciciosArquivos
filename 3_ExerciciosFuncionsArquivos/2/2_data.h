#ifndef _2_FECHA_H
#define _2_FECHA_H

#include <stdbool.h>

typedef struct date_t {

    int year;
    int month;
    int day;

} date_t;


int     days_in_month(int m, int year);
int     date_day_num(date_t* date);
bool    date_leap_year(int year);
bool    date_valid(date_t* date);

#endif
