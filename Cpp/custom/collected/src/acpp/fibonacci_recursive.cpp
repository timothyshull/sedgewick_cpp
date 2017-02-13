// Program 5.10 - Fibonacci numbers (recursive implementation)
#include "fibonacci_recursive.h"

int fibonacci(int i)
{
    if (i < 1) { return 0; }
    if (i == 1) { return 1; }
    return fibonacci(i - 1) + fibonacci(i - 2);
}
