// Program 5.2 - A questionable recursive program
#include "questionable_recursion.h"

int puzzle(int n)
{
    if (n == 1) { return 1; }
    if (n % 2 == 0) { return puzzle(n / 2); }
    return puzzle(3 * n + 1);
}
