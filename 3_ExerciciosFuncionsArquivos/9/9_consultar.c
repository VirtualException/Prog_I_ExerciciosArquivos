#include <stdlib.h>
#include "9_consultar.h"

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

/* Distancia entre datas */
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

/* Obter a información do tempo do día 'd' */
weather_data_t
weather_get_by_date(FILE* file, date_t d) {

    size_t n = 0;

    for (size_t i = 2000; i < d.year; i++) {
        n += date_leap_year(i) ? 366 : 365;
    }

    n += date_day_num(&d) - 1;

    /* Pór o cursor na posición do día 'n' */
    fseek(file, n * sizeof(weather_data_t), SEEK_SET);

    weather_data_t w = { 0 };
    fread(&w, sizeof(weather_data_t), 1, file);

    return w;

}

/* Precipitación media entre 'di' e 'df' */
float
weather_get_average_precip(FILE* file, date_t di, date_t df) {

    float total_sum = 0;

    /* Número de día do inicio */
    int start = 0;

    /* Total de días dende o inicio */
    int days = date_dist(di, df) + 1;

    for (size_t i = 2000; i < di.year; i++) {
        start += date_leap_year(i) ? 366 : 365;
    }

    start += date_day_num(&di) - 1;

    /* Sumar todos od datos de precipitación entre 'di' e 'df' */
    for (size_t i = 0; i < days; i++) {

        fseek(file, (start + i) * sizeof(weather_data_t), SEEK_SET);

        weather_data_t w = { 0 };
        fread(&w, sizeof(weather_data_t), 1, file);

        total_sum += w.precipitation;

    }

    return total_sum / days;

}

/* Leer a data dada polo usuario */
date_t
input_date() {

    date_t date = { 0 };

    printf("Dia: ");
    scanf("%d", &date.day);
    printf("Mes: ");
    scanf("%d", &date.month);
    printf("Año: ");
    scanf("%d", &date.year);

    if (!date_valid(&date) || date.year < 2000 || date.year > 2010) {
        printf("Data invalida ou fora dos limites\n");
        exit(1);
    }

    return date;

}


int
main(int argc, char** argv) {

    FILE* fwd = fopen("../weatherdata-420-72.dat", "r");

    if (fwd == NULL) {
        printf("Error abrindo o arquivo\n");
        exit(1);
    }

    /* Inicio da consulta */
get_op:

    printf("Que queres consultar?\n"
        "'1' : WeatherData dunha data especifica\n"
        "'2' : Precipitacion media entre dous datas\n");

    switch (getchar()) {

    /* WeatherData dunha data especifica */
    case '1':

        printf("Introduce a data de consulta:\n");

        date_t date = input_date();

        weather_data_t w = weather_get_by_date(fwd, date);

        printf("WeatherData nese día:\n");

        printf(WEATHER_FORMAT,
            w.date.day, w.date.month, w.date.year,
            w.longitude, w.latitude, w.elevation,
            w.max_temp, w.min_temp,
            w.precipitation, w.wind, w.rel_humidity, w.solar
        );

        break;

    /* Precipitacion media entre dous datas */
    case '2':

        printf("Introduce as datas de consulta:\n");

        date_t ini = input_date();
        date_t fin = input_date();

        if ((ini.year >  fin.year) ||
            (ini.year == fin.year && ini.month >  fin.month) ||
            (ini.year == fin.year && ini.month == fin.month && ini.day > fin.day)) {

            printf("Intervalo de datas invalido\n");
            return 1;

        }

        float p = weather_get_average_precip(fwd, ini, fin);

        printf("Precipitación media: %f\n", p);

        break;

    default:

        printf("Operación non recoñecida\n");
        goto get_op;

        break;
    }

    fclose(fwd);

    return 0;
}
