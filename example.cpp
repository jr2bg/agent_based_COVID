/*
https://coral.ise.lehigh.edu/jild13/2016/07/11/hello/


gcc -Wall -I/home/jr2bg/gsl/include -c <filename>.(c|cpp)
gcc -L/home/jr2bg/gsl/lib <filename>.o -lgsl -lgslcblas -lm


##############################################################################


https://askubuntu.com/questions/890027/installing-gsl-libraries-in-ubuntu-16-04-via-terminal
g++ -std=c++1X <your_program>.cpp -o <output_name> -lgsl -lgslcblas -lm

*/

#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>

int main (void)
{
    double x = 15.0;
    double y = gsl_sf_bessel_J0 (x);
    printf ("J0(%g) = %.18e/n", x, y);
    return 0;
}
