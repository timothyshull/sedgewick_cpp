#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include <cmath>

class Accumulator {
public:
    void add_data_value(double x);

    double mean() const noexcept
    {
        return _mean;
    }

    double var() const;

    double std_dev() const
    {
        return std::sqrt(this->var());
    }

    int count() const noexcept
    {
        return _count;
    }

private:
    int _count{0};
    double _sum{0.0};
    double _mean{0.0};
};

#endif // ACCUMULATOR_H
