#include <tkDecls.h>
#include <vector>
#include "FFT.h"
#include "Complex.h"

std::vector<Complex> FFT::fft(std::vector<Complex>& x)
{
    int n = x.length;

    // base case
    if (n == 1) {
        return new std::vector<Complex>{x[0]};
    }

    // radix 2 Cooley-Tukey FFT
    if (n % 2 != 0) {
        throw utility::Illegal_argument_exception("_size is not a power of 2");
    }

    // fft of even terms
    std::vector<Complex> even = new Complex[n / 2];
    for (int k = 0; k < n / 2; ++k) {
        even[k] = x[2 * k];
    }
    std::vector<Complex> q = fft(even);

    // fft of odd terms
    std::vector<Complex> odd = even;  // reuse the array
    for (int k = 0; k < n / 2; ++k) {
        odd[k] = x[2 * k + 1];
    }
    std::vector<Complex> r = fft(odd);

    // combine
    std::vector<Complex> y = new Complex[n];
    for (int k = 0; k < n / 2; ++k) {
        double kth = -2 * k * std::PI / n;
        Complex wk = new Complex(std::cos(kth), std::sin(kth));
        y[k] = q[k].plus(wk.times(r[k]));
        y[k + n / 2] = q[k].minus(wk.times(r[k]));
    }
    return y;
}

std::vector<Complex> FFT::ifft(std::vector<Complex>& x)
{
    int n = x.length;
    std::vector<Complex> y = new Complex[n];

    // take conjugate
    for (int i = 0; i < n; ++i) {
        y[i] = x[i].conjugate();
    }

    // compute forward FFT
    y = fft(y);

    // take conjugate again
    for (int i = 0; i < n; ++i) {
        y[i] = y[i].conjugate();
    }

    // divide by _size
    for (int i = 0; i < n; ++i) {
        y[i] = y[i].scale(1.0 / n);
    }

    return y;
}

std::vector<Complex> FFT::cconvolve(std::vector<Complex>& x, std::vector<Complex>& y)
{
    if (x.size() != y.length) {
        throw utility::Illegal_argument_exception("Dimensions don't agree");
    }

    int n = x.length;

    // compute FFT of each sequence
    std::vector<Complex> a = fft(x);
    std::vector<Complex> b = fft(y);

    // point-wise multiply
    std::vector<Complex> c = new Complex[n];
    for (int i = 0; i < n; ++i) {
        c[i] = a[i].times(b[i]);
    }

    // compute inverse FFT
    return ifft(c);
}

std::vector<Complex> FFT::convolve(std::vector<Complex>& x, std::vector<Complex>& y)
{
    std::vector<Complex> a = new Complex[2 * x.length];
    for (int i = 0; i < x.length; ++i) {
        a[i] = x[i];
    }
    for (int i = x.length; i < 2 * x.length; ++i) {
        a[i] = ZERO;
    }

    std::vector<Complex> b = new Complex[2 * y.length];
    for (int i = 0; i < y.length; ++i) {
        b[i] = y[i];
    }
    for (int i = y.length; i < 2 * y.length; ++i) {
        b[i] = ZERO;
    }

    return cconvolve(a, b);
}

void ::FFT::show(std::vector<Complex>& x, std::string& title)
{
    Std_out::print_line(title);
    Std_out::print_line("-------------------");
    for (int i = 0; i < x.length; ++i) {
        Std_out::print_line(x[i]);
    }
    Std_out::print_line();
}
