#ifndef _9_CONSULTAR_H
#define _9_CONSULTAR_H

#include <stdio.h>
#include <stdbool.h>

#define LINE_SIZE 256
#define N_ENTRIES 4018

typedef struct date_t {

    int year;
    int month;
    int day;

} date_t;

#define WEATHER_FORMAT "%d %d %d %f %f %d %f %f %f %f %f %f"

typedef struct weather_data_t {

    date_t  date;

    float   longitude;
    float   latitude;
    int     elevation;

    float   max_temp;
    float   min_temp;

    float   precipitation;
    float   wind;
    float   rel_humidity;
    float   solar;

} __attribute__((__packed__)) weather_data_t;


int days_in_month(int m, int year);
int date_day_num(date_t* date);
bool date_leap_year(int year);
bool date_valid(date_t* date);
int date_dist(date_t ini, date_t fin);

/* WeatherData Consulta_por_data(File* file, Data d) */
weather_data_t weather_get_by_date(FILE* file, date_t d);

/* float Consulta_precip_media(File* file, Data d1, Data d2) */
float weather_get_average_precip(FILE* file, date_t di, date_t df);

date_t input_date();

#endif
