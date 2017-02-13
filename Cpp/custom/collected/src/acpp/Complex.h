#ifndef COMPLEX_H
#define COMPLEX_H

#include <ostream>

class Complex {
public:
    Complex(double x, double y);

    inline double real() const noexcept { return _real; }

    inline double imag() const noexcept { return _imag; }

    Complex& operator*=(const Complex& rhs);

private:
    double _real;
    double _imag;
};

std::ostream& operator<<(std::ostream& os, const Complex& rhs);

#endif // COMPLEX_H
