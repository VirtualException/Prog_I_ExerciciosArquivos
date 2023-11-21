#include <stdio.h>
#include <stdlib.h>
#include "8_weather.h"

void
weather_parse(char* line, weather_data_t* w_out) {

    for (size_t i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\"' || line[i] == ',' || line[i] == '/') {
            line[i] = ' ';
        }
    }



    sscanf(line, WEATHER_FORMAT,
        &w_out->date.day, &w_out->date.month, &w_out->date.year,
        &w_out->longitude, &w_out->latitude, &w_out->elevation,
        &w_out->max_temp, &w_out->min_temp,
        &w_out->precipitation, &w_out->wind, &w_out->rel_humidity, &w_out->solar
    );

}

int
main(int argc, char** argv) {

    FILE* fin = fopen("../weatherdata-420-72.csv", "r");
    FILE* fout = fopen("../weatherdata-420-72.dat", "w");

    if (fin == NULL || fout == NULL) {
        printf("Error abrindo o arquivo\n");
        exit(1);
    }

    weather_data_t* weather_list = malloc(N_ENTRIES * sizeof(weather_data_t));

    char line[LINE_SIZE] = { 0 };
    int index = 0;

    /* Ignore first line */
    fgets(line, LINE_SIZE, fin);

    while (fgets(line, LINE_SIZE, fin) != NULL) {

        weather_parse(line, &weather_list[index++]);

    };

    fwrite(weather_list, sizeof(weather_data_t), N_ENTRIES, fout);

    fclose(fin);
    fclose(fout);

    return 0;
}
