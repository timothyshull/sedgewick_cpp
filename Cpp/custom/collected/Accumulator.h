#ifndef COLLECTED_ACCUMULATOR_H
#define COLLECTED_ACCUMULATOR_H

#include<cmath>

template<class T, class Enable = void>
class Accumulator {};

template<typename Float_type>
class Accumulator<Float_type, typename std::enable_if<std::is_floating_point<Float_type>::value>::type> {
    int n{0};
    Float_type sum{0.0};
    Float_type mu{0.0};

public:
    void add_value(Float_type x) {
        n++;
        Float_type delta{x - mu};
        mu += delta / n;
        sum += static_cast<Float_type>(n - 1) / static_cast<Float_type>(n) * delta * delta;
    }

    inline Float_type mean() { return mu; }

    inline Float_type var() { return static_cast<Float_type>(sum / (n - 1)); }

    inline Float_type std_dev() { return static_cast<Float_type>(std::sqrt(this->var())); }

    inline int count() { return n; }
};

#endif //COLLECTED_ACCUMULATOR_H
