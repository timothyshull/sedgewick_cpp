#include "Interval_1d.h"
#include "utility.h"

bool Min_endpoint_comparator::operator()(const Interval_1d& a, const Interval_1d& b)
{
    if (a._min < b._min) { return true; }
    else if (a._min > b._min) { return false; }
    return a._max < b._max;
}

bool Max_endpoint_comparator::operator()(const Interval_1d& a, const Interval_1d& b)
{
    if (a._max < b._max) { return true; }
    else if (a._max > b._max) { return false; }
    return a._min < b._min;
}

bool Length_comparator::operator()(const Interval_1d& a, const Interval_1d& b)
{
    return a.length() < b.length();
}

Interval_1d::Interval_1d(double min, double max) : _min{min == 0.0 ? 0.0 : min}, _max{max == 0.0 ? 0.0 : max}
{
    if (std::isinf(min) || std::isinf(max)) {
        throw utility::Illegal_argument_exception{"Endpoints must be finite"};
    }
    if (std::isnan(min) || std::isnan(max)) {
        throw utility::Illegal_argument_exception{"Endpoints cannot be NaN"};
    }

    if (min > max) { throw utility::Illegal_argument_exception("Illegal interval"); }
}

bool Interval_1d::intersects(const Interval_1d& rhs) const
{
    if (_max < rhs._min) { return false; }
    return rhs._max >= _min;
}

bool Interval_1d::contains(double x) const
{
    return (_min <= x) && (x <= _max);
}

double Interval_1d::length() const
{
    return _max - _min;
}

std::string Interval_1d::to_string() const
{
    return "Interval_1d[" + std::to_string(_min) + ", " + std::to_string(_max) + "]";
}

bool Interval_1d::operator==(const Interval_1d& rhs) const
{
    return _min == rhs._min && _max == rhs._max;
}

std::size_t Interval_1d::hash_code() const
{
    std::size_t hash1{std::hash<double>{}(_min)};
    std::size_t hash2{std::hash<double>{}(_max)};
    return 31 * hash1 + hash2;
}

std::ostream& operator<<(std::ostream& os, Interval_1d& out)
{
    return os << out.to_string();
}
