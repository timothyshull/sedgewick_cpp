#include<iostream>
#include<cstdlib>
#include<cmath>
#include"Complex.h"

using std::cin;
using std::cout;

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    cout << n << " complex roots of unity" << "\n";
    float theta;
    Complex t;
    Complex x;
    for (int k = 0; k < n; k++) {
        theta = 2.0 * 3.14159 * k / n;
        t = Complex(cos(theta), sin(theta));
        x = t;
        cout << k << ": " << t << "  ";
        for (int j = 0; j < n - 1; j++) { x *= t; }
        cout << x << "\n";
    }
    return 0;
}

