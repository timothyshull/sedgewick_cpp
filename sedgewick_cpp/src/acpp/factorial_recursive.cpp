// Program 5.1 - Factorial function (recursive implementation)
#include "factorial_recursive.h"

int factorial(int n)
{
    if (n == 0) { return 1; }
    return n * factorial(n - 1);
}
