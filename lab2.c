#include <stdio.h>
#include <stdlib.h>

int power(int x, int y)
{
    int sum = 0;
    int summing = 0;
    asm(
        "   movl $0, %%eax                      \n"//set register eax to 0
        "   add %[x], %%eax                     \n"//enter x at register %eax
        "   add %[y], %%eax                     \n"//add y with conents of %eax(x)
        "   jo overflow                         \n"//if overflow flag is set, jump
        "   movl %%eax, %[sum]                  \n"//if overflow flag is not set, set value in eax to summing
        "   jmp done                            \n"//
        "   overflow: movl $0x01, %[summing]    \n"//save 1 in overflow check
        "done: nop                              \n"//
        :   [summing] "=m" (summing)//outputjj
        :   [x] "m" (x),//input
            [y] "m" (y),
            [sum] "m" (sum)
        :   "eax"//the required acknoledgement of register used
        );

    if(summing)
    {
        printf("overflow has occured.");
    }
    
    return sum;
}

int main(int argc, char * argv[])
{
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    printf("original two values = %d %d\n", x, y);
    argc = power(x, y);
    printf("using the assembly code: sum value = %d \n", argc);

    return 0;
}
