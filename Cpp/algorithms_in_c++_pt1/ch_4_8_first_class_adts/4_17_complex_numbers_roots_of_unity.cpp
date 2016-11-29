#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include "COMPLEX.cxx"

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    cout << N << " complex roots of unity" << endl;
    for (int k = 0; k < N; k++) {
        float theta = 2.0 * 3.14159 * k / N;
        Complex t(cos(theta), sin(theta)), x = t;
        cout << k << ": " << t << "  ";
        for (int j = 0; j < N - 1; j++) x *= t;
        cout << x << endl;
    }
}