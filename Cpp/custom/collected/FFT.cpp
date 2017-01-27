#include <vector>

#include "FFT.h"
#include "utility.h"
#include "Std_out.h"

std::vector<Complex> FFT::fft(std::vector<Complex>& x)
{
    auto n = x.size();

    if (n == 1) {
        return std::vector<Complex>{x[0]};
    }

    if (n % 2 != 0) {
        throw utility::Illegal_argument_exception("_size is not a power of 2");
    }

    std::vector<Complex> even;
    even.reserve(n / 2);
    for (int k{0}; k < n / 2; ++k) {
        even[k] = x[2 * k];
    }
    std::vector<Complex> q = fft(even);

    std::vector<Complex> odd = even;
    for (int k{0}; k < n / 2; ++k) {
        odd[k] = x[2 * k + 1];
    }
    std::vector<Complex> r = fft(odd);

    std::vector<Complex> y;
    y.reserve(n);
    for (int k{0}; k < n / 2; ++k) {
        double kth = -2 * k * pi / n;
        Complex wk{std::cos(kth), std::sin(kth)};
        Complex tmp{wk.times(r[k])};
        y[k] = q[k].plus(tmp);
        y[k + n / 2] = q[k].minus(tmp);
    }
    return y;
}

std::vector<Complex> FFT::ifft(std::vector<Complex>& x)
{
    auto n = x.size();
    std::vector<Complex> y;
    y.reserve(n);

    for (int i{0}; i < n; ++i) {
        y[i] = x[i].conjugate();
    }

    y = fft(y);

    for (int i{0}; i < n; ++i) {
        y[i] = y[i].conjugate();
    }

    for (int i{0}; i < n; ++i) {
        y[i] = y[i].scale(1.0 / n);
    }

    return y;
}

std::vector<Complex> FFT::cconvolve(std::vector<Complex>& x, std::vector<Complex>& y)
{
    if (x.size() != y.size()) {
        throw utility::Illegal_argument_exception("Dimensions don't agree");
    }

    auto n = x.size();

    std::vector<Complex> a = fft(x);
    std::vector<Complex> b = fft(y);

    std::vector<Complex> c;
    c.reserve(n);
    for (int i{0}; i < n; ++i) {
        c[i] = a[i].times(b[i]);
    }

    return ifft(c);
}

std::vector<Complex> FFT::convolve(std::vector<Complex>& x, std::vector<Complex>& y)
{
    auto n = x.size();
    std::vector<Complex> a;
    a.reserve(2 * n);
    for (int i{0}; i < n; ++i) {
        a[i] = x[i];
    }
    for (auto i = n; i < 2 * n; ++i) {
        a[i] = zero;
    }

    auto m = y.size();
    std::vector<Complex> b;
    b.reserve(2 * m);
    for (int i{0}; i < m; ++i) {
        b[i] = y[i];
    }
    for (auto i = m; i < 2 * m; ++i) {
        b[i] = zero;
    }

    return cconvolve(a, b);
}

void ::FFT::show(std::vector<Complex>& x, std::string&& title)
{
    Std_out::print_line(title);
    Std_out::print_line("-------------------");
    for (int i{0}; i < x.size(); ++i) {
        Std_out::print_line(x[i]);
    }
    Std_out::print_line();
}
