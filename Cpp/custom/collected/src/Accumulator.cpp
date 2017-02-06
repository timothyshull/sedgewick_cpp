#include <limits>

#include "Accumulator.h"

void Accumulator::add_data_value(double x)
{
    ++_count;
    double delta{x - _mean};
    _mean += delta / _count;
    _sum += static_cast<double>(_count - 1) / _count * delta * delta;
}

double Accumulator::var() const
{
    if (_count < 2) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return _sum / (_count - 1);
}