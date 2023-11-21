#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "4_distancia.h"

/* Days at avery month in a normal year */
int days_per_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool
date_leap_year(int year) {

    if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) {
        return true;
    }

    return false;

}

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

int
days_in_month(int m, int year) {

    if (m == 2 && date_leap_year(year)) return 29;
    else return days_per_month[m];

}

int
date_day_num(date_t* date) {

    if (!date_valid(date)) {

        printf("Data invalida\n");
        exit(1);

    }

    int days = 0;

    for (int m = 1; m < date->month; m++) {
        days += days_in_month(m, date->year);
    }

    days += date->day;

    return days;

}


date_t
data_read() {

    date_t date = { 0 };

    printf("Dia: ");
    scanf("%d", &date.day);
    printf("Mes: ");
    scanf("%d", &date.month);
    printf("Año: ");
    scanf("%d", &date.year);

    if (!date_valid(&date)) {

        printf("Invalid date\n");
        exit(1);

    }

    return date;

}

int
date_dist(date_t ini, date_t fin) {

    /* inicial date < final date */

    if ((ini.year >  fin.year) ||
        (ini.year == fin.year && ini.month >  fin.month) ||
        (ini.year == fin.year && ini.month == fin.month && ini.day > fin.day)) {

        printf("Datas invalidas\n");
        exit(1);

    }

    if (ini.year == fin.year) {

        /* Distance between days of same year*/
        return date_day_num(&fin) - date_day_num(&ini);


    }
    else {

        int count = 0;
        int year_days = date_leap_year(ini.year) ? 366 : 365;

        /* Days in the years between */

        for (size_t k = ini.year + 1; k < fin.year; k++) {

            count += 365;

            if (date_leap_year(k)) count++;

        }

        count += (year_days - date_day_num(&ini)) + date_day_num(&fin); 

        return count;

    }


    return 0;
}

void
date_print(date_t d, char f[]) {

    if (f[0] == '1') {
        printf("%d/%d/%d\n", d.day, d.month, d.year);
    }
    else if (f[0] == '2') {
        printf("%d/%d/%d\n", d.month, d.day, d.year);
    }

    return;

}

int
main(int argc, char** argv) {

    printf("\nData inicial\n");
    date_t ini = data_read();
    date_print(ini, "1");

    printf("\nData final\n");
    date_t fin = data_read();
    date_print(fin, "1");

    printf("\nDistancia entre datas: %d\n", date_dist(ini, fin));

    return 0;
}
