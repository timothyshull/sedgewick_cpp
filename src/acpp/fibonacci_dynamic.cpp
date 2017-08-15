// Program 5.11 - Fibonacci numbers (dynamic programming)
#include <vector>
#include "fibonacci_dynamic.h"

int fibonacci(int i)
{
    const static std::size_t max_n{100};
    static std::vector<int> known_fibonacci(max_n, 0);
    if (known_fibonacci[i] != 0) { return known_fibonacci[i]; }
    auto t = i;
    if (i < 0) { return 0; }
    if (i > 1) { t = fibonacci(i - 1) + fibonacci(i - 2); }
    known_fibonacci[i] = t;
    return t;
}