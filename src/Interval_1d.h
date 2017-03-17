#ifndef INTERVAL_1D_H
#define INTERVAL_1D_H

#include <string>

class Interval_1d;

struct Min_endpoint_comparator {
    bool operator()(const Interval_1d& a, const Interval_1d& b);
};

struct Max_endpoint_comparator {
    bool operator()(const Interval_1d& a, const Interval_1d& b);
};

struct Length_comparator {
    bool operator()(const Interval_1d& a, const Interval_1d& b);
};

class Interval_1d {
public:
    constexpr static Min_endpoint_comparator min_endpoint_order{};
    constexpr static Max_endpoint_comparator max_endpoint_order{};
    constexpr static Length_comparator length_order{};

    Interval_1d() = default;

    Interval_1d(const Interval_1d&) = default;

    Interval_1d(Interval_1d&&) = default;

    ~Interval_1d() = default;

    Interval_1d& operator=(const Interval_1d&) = default;

    Interval_1d& operator=(Interval_1d&&) = default;

    Interval_1d(double min, double max);

    inline double left() const noexcept { return _min; }

    inline double right() const noexcept { return _max; }

    inline double min() const noexcept { return _min; }

    inline double max() const noexcept { return _max; }

    bool intersects(const Interval_1d& rhs) const;

    bool contains(double x) const;

    double length() const;

    std::string to_string() const;

    bool operator==(const Interval_1d& rhs) const;

    std::size_t hash_code() const;

private:
    // logically const
    double _min;
    // logically const
    double _max;

    friend struct Min_endpoint_comparator;
    friend struct Max_endpoint_comparator;
    friend struct Length_comparator;
};

std::ostream& operator<<(std::ostream& os, Interval_1d& out);

#endif // INTERVAL_1D_H
