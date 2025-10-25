#include <stdio.h>

int main ()
{
    int rulex = 0;
    int ruley = 0;
    int i = 0;
	while (i < 35)
	{
		int j = 0;
		while (j < 35)
		{
			// #ifdef DEBUG_DS
			printf ("rulex : %d\n", (rulex + j));
			printf ("ruley : %d\n", (ruley + i));
			printf ("draw square loop !\n");
			// printf ("ruley : %d\n", (ruley + y));
			// #endif
			printf ("pixel have been put in x : %d and y : %d\n", j + rulex, i + ruley);
			j++;
		}
		// while (1);
		i++;
	}
}