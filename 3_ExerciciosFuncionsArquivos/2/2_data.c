#include <stdio.h>
#include <stdlib.h>
#include "2_data.h"


/* Días cada mes nun ano normal */
int days_per_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/* Días en cada mes */
int
days_in_month(int m, int year) {

    if (m == 2 && date_leap_year(year)) return 29;
    else return days_per_month[m];

}

/* Comprobar se 'year' é bisiesto */
bool
date_leap_year(int year) {

    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        return true;
    }

    return false;

}

/* Comprobar se a data é valida */
bool
date_valid(date_t* date) {

    if (date->month < 1 || date->month > 12) {
        return false;
    }
    if (date->day < 1 || date->day > days_in_month(date->month, date->year)) {
        return false;
    }

    return true;
}

/* Número do día do ano */
int
date_day_num(date_t* date) {

    if (!date_valid(date)) {

        printf("Invalid date\n");
        exit(1);

    }

    int days = 0;

    for (int m = 1; m < date->month; m++) {
        days += days_in_month(m, date->year);
    }

    days += date->day;

    return days;

}

int
main(int argc, char** argv) {

    date_t date = { 0 };

    printf("Dia: ");
    scanf("%d", &date.day);
    printf("Mes: ");
    scanf("%d", &date.month);
    printf("Año: ");
    scanf("%d", &date.year);

    printf("Numero de dia: %d\n", date_day_num(&date));

    return 0;
}
