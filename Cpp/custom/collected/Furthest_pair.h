#ifndef FURTHEST_PAIR_H
#define FURTHEST_PAIR_H

#include <limits>
#include <vector>
#include "Point_2d.h"

class Furthest_pair {
public:
    Furthest_pair(std::vector<Point_2d>& points);
    Point_2d either();
    Point_2d other();
    double distance();

private:
    Point_2d best1;
    Point_2d best2;
    double bestDistanceSquared = std::numeric_limits<double>::infinity();
};

#endif // FURTHEST_PAIR_H
