#include <stdio.h>
#include <math.h>

int main ()
{
    /*
    0x : 420.000000 -> 420
    0y : 83.957751 -> 83

    2559x : 145.607353 -> 145
    2559y : 34.532352 -> 34

    */
    /*
    151.392647
    -262.467648
    */
    double dx = 5.55;
    double dy = 5.55;
    printf ("dx2 : %f\n", (dx * dx));
    printf ("dy2 : %f\n", (dy * dy));
    printf ("(dx * dx + dy * dy) : %f\n", (dx * dx + dy * dy));
    printf ("sqrt(dx * dx + dy * dy) : %f\n", sqrt(dx * dx + dy * dy));
}