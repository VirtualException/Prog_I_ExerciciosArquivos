#ifndef _8_WEATHER_H
#define _8_WEATHER_H

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

void weather_parse(char* line, weather_data_t* w_out);

#endif
