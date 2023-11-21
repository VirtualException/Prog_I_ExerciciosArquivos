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

date_t  data_read();                        /* Date Ler();                                  */
int     date_dist(date_t i, date_t f);      /* int  CalcularDistancia(Date d1, Date d2);    */
void    date_print(date_t d, char f[]);     /* void Mostrar(Date d, char f[]);              */
