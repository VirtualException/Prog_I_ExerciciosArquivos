#include <stdio.h>
#include "7_eliminar.h"

/* Reemplazar os caracteres '"', ',' e '/' por un espazo en branco */
void
edit_line(char* line) {

    for (size_t i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\"' || line[i] == ',' || line[i] == '/') {
            line[i] = ' ';
        }
    }

}

int
main(int argc, char** argv) {

    FILE* fin   = fopen("./weatherdata-420-72.csv", "r");
    FILE* fout  = fopen("./7_weatherdata-420-72_out.csv", "w");

    if (fin == NULL || fout == NULL) {
        printf("Error abrindo o arquivo\n");
        return 1;
    }

    /* Ignorar a primeira liña (liberando a memoria usada do stack) */
    {
        char ignore[LINE_SIZE] = { 0 };
        fgets(ignore, LINE_SIZE, fin);
    }

    char* status = 0;

    do {

        char line[LINE_SIZE] = { 0 };

        status = fgets(line, LINE_SIZE, fin);

        edit_line(line);

        fprintf(fout, "%s", line);


    }  while (status != NULL);

    fclose(fin);
    fclose(fout);

    return 0;
}
