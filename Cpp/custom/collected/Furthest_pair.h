#ifndef FURTHEST_PAIR_H
#define FURTHEST_PAIR_H

#include <limits>
#include <vector>
#include <cmath>

#include "Point_2d.h"

class Furthest_pair {
public:
    Furthest_pair(std::vector<Point_2d>& points);

    inline Point_2d either() const noexcept { return _best1; }

    inline Point_2d other() const noexcept { return _best2; }

    inline double distance() const { return std::sqrt(_best_distance_squared); }

private:
    Point_2d _best1;
    Point_2d _best2;
    double _best_distance_squared = std::numeric_limits<double>::infinity();
};

#endif // FURTHEST_PAIR_H
