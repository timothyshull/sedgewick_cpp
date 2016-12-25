#include <iostream>
#include <stdlib.h>
#include "POLY.cxx"

using std::cout;

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);
    float p = atof(argv[2]);
    cout << "Binomial coefficients" << "\n";
    POLY<int> x(1, 1), one(1, 0), t = x + one, y = t;
    for (int i = 0; i < N; i++) {
        y = y * t;
        cout << y << "\n";
    }
    cout << y.eval(p) << "\n";
    return 0;
}

