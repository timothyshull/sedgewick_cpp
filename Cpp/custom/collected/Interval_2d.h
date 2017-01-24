#ifndef INTERVAL_2D_H
#define INTERVAL_2D_H

#include "Interval_1d.h"
#include "Point_2d.h"

class Interval_2d {
public:
    Interval_2d(Interval_1d& x, Interval_1d& y);

    bool intersects(Interval_2d& that);

    bool contains(Point_2d& that);

    double area();

    std::string to_string();

    bool operator==(Interval_2d& rhs);

    int hashCode();

    void draw();

private:
    const Interval_1d x;
    const Interval_1d y;
};

#endif // INTERVAL_2D_H
