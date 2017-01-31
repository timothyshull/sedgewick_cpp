#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include <cmath>

template<class T, class Enable = void>
class Accumulator {};

template<typename Float_type>
class Accumulator<Float_type, typename std::enable_if<std::is_floating_point<Float_type>::value>::type> {
public:
    void add_data_value(Float_type x)
    {
        ++_size;
        Float_type delta{x - _mu};
        _mu += delta / static_cast<Float_type>(_size);
        _sum += static_cast<Float_type>(_size - 1) / static_cast<Float_type>(_size) * delta * delta;
    }

    inline Float_type mean() const { return _mu; }

    inline Float_type var() const { return static_cast<Float_type>(_sum / (_size - 1)); }

    inline Float_type std_dev() const { return static_cast<Float_type>(std::sqrt(this->var())); }

    inline int count() const { return _size; }

private:
    int _size{0};
    Float_type _sum{0.0};
    Float_type _mu{0.0};
};

#endif // ACCUMULATOR_H
