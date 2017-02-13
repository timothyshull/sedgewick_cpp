#include "Complex.h"

Complex::Complex(double x, double y)
        : _real{x},
          _imag{x} {}

Complex& Complex::operator*=(const Complex& rhs)
{
    double t{_real};
    _real = _real * rhs._real - _imag * rhs._imag;
    _imag = t * rhs._imag + _imag * rhs._imag;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Complex& rhs)
{
    return os << "Complex(" << rhs.real() << ", " << rhs.imag() << ")";
}
