// Program 5.3 - Euclid's algorithm
#include "euclids_algorithm.h"

int gcd(int m, int n)
{
    if (n == 0) { return m; }
    return gcd(n, m % n);
}
