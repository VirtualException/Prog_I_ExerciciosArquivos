#include <stdio.h>
#include "1_gcd.h"

/* Greatest Common Divisor */

int
gcd(int a, int b) {

    // o mesmo ca función abs()
    if (a < 0 ) a = -a;
    if (b < 0 ) b = -b;

    for (int d = MIN(a, b); d >= 1; d--) {
        if (a % d == 0 && b % d == 0) {
            return d;
        }
    }

    return 0;
}

int
main() {

    int a = 0;
    int b = 0;
    int r = 0;

    printf("Dame dous valores enteros:\n");
    scanf("%d", &a);
    scanf("%d", &b);

    r = gcd(a, b);
    printf("Maximo comun divisor de %d y %d: %d\n", a, b, r);

    return 0;
}
