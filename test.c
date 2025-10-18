// C program for DDA line generation

#include <math.h>
#include <stdio.h>
#include <unistd.h>
// Function for finding absolute value
int abs(int n) { return ((n > 0) ? n : (n * (-1))); }

// DDA Function for line generation
void DDA(int X0, int Y0, int X1, int Y1)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;

    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // calculate increment in x & y for each steps
    double Xinc = dx / (double)steps;
    double Yinc = dy / (double)steps;

    // Put pixel for each step
    double X = X0;
    double Y = Y0;
    printf("x inc : %f , x inc : %f\n", Xinc, Yinc); // put pixel at (X,Y)
    double V = 1 + Xinc;
    printf("V : %f\n", V);
    for (int i = 0; i <= steps; i++) {
        printf("[%f , %f]\n", round(X), round(Y)); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
        sleep(1); // for visualization of line-
                    // generation step by step
    }
}

// Driver program
int main()
{
    int X0 = 20, Y0 = 2, X1 = 4, Y1 = 16;

    // Function call
    DDA(X0, Y0, X1, Y1);
    return 0;
}