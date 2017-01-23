#ifndef FFT_H
#define FFT_H

#include <vector>
#include "Complex.h"

namespace FFT {
const static Complex ZERO = Complex(0, 0);
    std::vector<Complex> fft(std::vector<Complex>& x);
    std::vector<Complex> ifft(std::vector<Complex>& x);
    std::vector<Complex> cconvolve(std::vector<Complex>& x, std::vector<Complex>& y);
    std::vector<Complex> convolve(std::vector<Complex>& x, std::vector<Complex>& y);
    void show(std::vector<Complex>& x, std::string& title);
};

#endif // FFT_H
