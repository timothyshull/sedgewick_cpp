#include <cmath>

double lg_factorial(int n) {
    if (n == 1) {
        return 0;
    } else {
        return log2(n) + lg_factorial(n - 1);
    }
}