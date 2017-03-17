#include <gsl/gsl_util>

#include "Vector.h"
#include "utility.h"

Vector::Vector(int d)
        : _dimension{d},
          _data(static_cast<std::vector<double>::size_type>(d)) {}

Vector::Vector(std::initializer_list<double>& a)
        : _dimension{gsl::narrow<int, std::initializer_list<double>::size_type>(a.size())},
          _data{a} {}

double Vector::dot(Vector& that)
{
    if (_dimension != that._dimension) { throw utility::Illegal_argument_exception("Dimensions don't agree"); }
    double sum{0.0};
    for (int i{0}; i < _dimension; ++i) {
        sum = sum + (_data[i] * that._data[i]);
    }
    return sum;
}

double Vector::magnitude()
{
    return std::sqrt(dot(*this));
}

double Vector::distance_to(Vector& rhs)
{
    if (_dimension != rhs._dimension) { throw utility::Illegal_argument_exception("Dimensions don't agree"); }
    return minus(rhs).magnitude();
}

Vector Vector::plus(Vector& rhs)
{
    if (_dimension != rhs._dimension) { throw utility::Illegal_argument_exception("Dimensions don't agree"); }
    Vector c{_dimension};
    for (int i{0}; i < _dimension; ++i) {
        c._data[i] = _data[i] + rhs._data[i];
    }
    return c;
}

Vector Vector::minus(Vector& rhs)
{
    if (_dimension != rhs._dimension) { throw utility::Illegal_argument_exception("Dimensions don't agree"); }
    Vector c{_dimension};
    for (int i{0}; i < _dimension; ++i) {
        c._data[i] = _data[i] - rhs._data[i];
    }
    return c;
}

Vector Vector::times(double alpha)
{
    Vector c{_dimension};
    for (int i{0}; i < _dimension; ++i) {
        c._data[i] = alpha * _data[i];
    }
    return c;
}

Vector Vector::scale(double alpha)
{
    Vector c{_dimension};
    for (int i{0}; i < _dimension; ++i) {
        c._data[i] = alpha * _data[i];
    }
    return c;
}

Vector Vector::direction()
{
    if (magnitude() == 0.0) { throw utility::Arithmetic_exception{"Zero-vector has no direction"}; }
    return times(1.0 / magnitude());
}

std::string Vector::to_string()
{
    std::stringstream ss;
    for (auto i : _data) {
        ss << i << " ";
    }
    return ss.str();
}
