#include <stdio.h>

int main ()
{
    /*
    0x : 420.000000 -> 420
    0y : 83.957751 -> 83

    2559x : 145.607353 -> 145
    2559y : 34.532352 -> 34

    */
    double x1 = 420.000000;
    double x2 = 145.607353;
    double y1 = 83.957751;
    double y2 = 34.532352;
    int tx1 = (int)x1;
    int tx2 = (int)x2;
    int ty1 = (int)y1;
    int ty2 = (int)y2;
    printf ("%d\n", tx1);
    printf ("%d\n", tx2);
    printf ("%d\n", ty1);
    printf ("%d\n", ty2);
}