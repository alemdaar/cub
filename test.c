#include <stdio.h>

int main ()
{
    int x = 13;
    int y = 12;
    int z = 13;

    if (x == (y || z))
        printf ("12 || 8\n");
    // else if (x == (13 || 8))
    //     printf ("13 || 8\n");
    else
        printf ("else\n");
    
}