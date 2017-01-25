#include <vector>
#include "Complex.h"
#include "Std_random.h"
#include "FFT.h"

int main(int argc, char* argv[])
{
    int n{utility::str_to_num(argv[1])};
    std::vector<Complex> x;
    x.reserve(n);

    for (int i = 0; i < n; ++i) {
        x[i] = Complex(i, 0);
        x[i] = Complex(Std_random::uniform(-1.0, 1.0), 0);
    }
    FFT::show(x, "x");

    std::vector<Complex> y{FFT::fft(x)};
    FFT::show(y, "y = fft(x)");

    std::vector<Complex> z{FFT::ifft(y)};
    FFT::show(z, "z = ifft(y)");

    std::vector<Complex> c{FFT::cconvolve(x, x)};
    FFT::show(c, "c = cconvolve(x, x)");

    std::vector<Complex> d{FFT::convolve(x, x)};
    FFT::show(d, "d = convolve(x, x)");
    return 0;
}