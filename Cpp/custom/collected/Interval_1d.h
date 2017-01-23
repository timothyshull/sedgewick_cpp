#ifndef INTERVAL_1D_H
#define INTERVAL_1D_H

#include <string>

struct Min_endpoint_comparator {
    bool operator()(Interval_1d& a, Interval_1d& b);
};

struct Max_endpoint_comparator {
    bool operator()(Interval_1d& a, Interval_1d& b);
};

struct Length_comparator {
    bool operator()(Interval_1d& a, Interval_1d& b);
};

class Interval_1d {
public:
    const static Min_endpoint_comparator MIN_ENDPOINT_ORDER{};
    const static Max_endpoint_comparator MAX_ENDPOINT_ORDER{};
    const static Length_comparator LENGTH_ORDER{};

    Interval_1d(double min, double max);

    double left();

    double right();

    double min();

    double max();

    bool intersects(Interval_1d& that);

    bool contains(double x);

    double length();

    std::string toString();

    bool operator==(Interval_1d& rhs);

    int hashCode();

private:
    const double min;
    const double max;
};

std::ostream& operator<<(std::ostream& os, Interval_1d& out);

#endif // INTERVAL_1D_H
