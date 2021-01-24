#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double getPeriod(double length)
{
    double period;
    double constant = 2.01;
    asm(
            "   fldl %[length]      \n"
            "   fsqrt               \n"
            "   fldl %[constant]    \n"
            "   fmul                \n"
            "   fstpl %[period]     \n"
            :[period] "=m" (period),
            [constant] "=m" (constant)
            :[length] "m" (length)

    );
    return period;
}

int main(int argc, char * argv[])
{
    double length = atoi(argv[1]);
    printf("the length you entered was %f\n", length);
    double period = getPeriod(length);
    printf("the period is %f\n", period); 
    return 0;
}
