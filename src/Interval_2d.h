#ifndef INTERVAL_2D_H
#define INTERVAL_2D_H

#include "Interval_1d.h"
#include "Point_2d.h"

class Interval_2d {
public:
    Interval_2d() = default;

    Interval_2d(const Interval_2d&) = default;

    Interval_2d(Interval_2d&&) = default;

    ~Interval_2d() = default;

    Interval_2d& operator=(const Interval_2d&) = default;

    Interval_2d& operator=(Interval_2d&&) = default;

    Interval_2d(const Interval_1d& x, const Interval_1d& y);

    bool intersects(const Interval_2d& that) const;

    bool contains(const Point_2d& rhs) const;

    double area() const;

    std::string to_string() const;

    bool operator==(const Interval_2d& rhs) const;

    std::size_t hash_code() const;

    void draw() const;

private:
    // logically const
    Interval_1d _x;
    // logically const
    Interval_1d _y;
};

std::ostream& operator<<(std::ostream& os, const Interval_2d& out);

#endif // INTERVAL_2D_H
