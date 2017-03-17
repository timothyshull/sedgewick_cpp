#include <string>
#include <sstream>
#include <cmath>
#include "Complex.h"

Complex::Complex(double real, double imaginary) : _real{real}, _imag{imaginary} {}

std::string Complex::to_string() const
{
    std::stringstream ss;
    ss << "Complex(real: " << _real << ", imaginary: " << _imag << ")\n";
    return ss.str();
}

// TODO: need to handle overflow here
double Complex::abs() const
{
    return std::sqrt(std::pow(_real, 2) + std::pow(_imag, 2));
}

double Complex::phase() const
{
    return atan2(_imag, _real);
}

Complex Complex::plus(Complex& that) const
{
    return {this->_real + that._real, this->_imag + that._imag};
}

Complex Complex::minus(Complex& that) const
{
    return {this->_real - that._real, this->_imag - that._imag};
}

Complex Complex::times(Complex& that) const
{
    double real = this->_real * that._real - this->_imag * that._imag;
    double imaginary = this->_real * that._imag + this->_imag * that._real;
    return Complex(real, imaginary);
}

Complex Complex::scale(double alpha) const
{
    return Complex(alpha * _real, alpha * _imag);
}

Complex Complex::times(double alpha) const
{
    return Complex(alpha * _real, alpha * _imag);
}

Complex Complex::conjugate() const
{
    return Complex(_real, -_imag);
}

Complex Complex::reciprocal() const
{
    double scale = _real * _real + _imag * _imag;
    return Complex(_real / scale, -_imag / scale);
}

Complex Complex::divides(Complex& that) const
{
    Complex reciprocal = that.reciprocal();
    return this->times(reciprocal);
}

Complex Complex::exp() const
{
    return Complex(std::exp(_real) * std::cos(_imag), std::exp(_real) * std::sin(_imag));
}

Complex Complex::sin() const
{
    return Complex(std::sin(_real) * std::cosh(_imag), std::cos(_real) * std::sinh(_imag));
}

Complex Complex::cos() const
{
    return Complex(std::cos(_real) * std::cosh(_imag), -std::sin(_real) * std::sinh(_imag));
}

Complex Complex::tan() const
{
    Complex sin = this->sin();
    Complex cos = this->cos();
    return sin.divides(cos);
}

std::ostream& operator<<(std::ostream& os, Complex& out)
{
    return os << out.to_string();
}
