#ifndef CLOSEST_PAIR_H
#define CLOSEST_PAIR_H

#include <limits>
#include <functional>
#include <vector>
#include "Point_2d.h"

class Closest_pair {
public:
    Closest_pair(std::vector<Point_2d>& points);

    double closest(std::vector<Point_2d>& points_by_x, std::vector<Point_2d>& points_by_y, std::vector<Point_2d>& aux, int lo, int hi);

    inline Point_2d either() const noexcept { return _best1; }

    inline Point_2d other() const noexcept { return _best2; }

    inline double distance() const noexcept { return _best_distance; }

private:
    Point_2d _best1;
    Point_2d _best2;
    double _best_distance = std::numeric_limits<double>::infinity();

    template<typename T>
    inline bool less(T& v, T& w) const { return v < w; }

    template<typename T>
    void merge(std::vector<T>& a, std::vector<T>& aux, int lo, int mid, int hi)
    {
        for (int k{lo}; k <= hi; ++k) {
            aux[k] = a[k];
        }

        int i = lo, j = mid + 1;
        for (int k{lo}; k <= hi; ++k) {
            if (i > mid) { a[k] = aux[j++]; }
            else if (j > hi) { a[k] = aux[i++]; }
            else if (less(aux[j], aux[i])) { a[k] = aux[j++]; }
            else { a[k] = aux[i++]; }
        }
    }
};

#endif // CLOSEST_PAIR_H
