#ifndef CLOSEST_PAIR_H
#define CLOSEST_PAIR_H

#include <limits>
#include <functional>
#include <vector>
#include "Point_2d.h"

class Closest_pair {
public:
    Closest_pair(std::vector<Point_2d>& points);
    double closest(std::vector<Point_2d>& pointsByX, std::vector<Point_2d>& pointsByY, std::vector<Point_2d>& aux, int lo, int hi);
    Point_2d either();
    Point_2d other();
    double distance();
private:
    Point_2d best1;
    Point_2d best2;
    double bestDistance = std::numeric_limits<double>::infinity();

    template<typename T>
    bool less(T& v, T& w)
    {
        return v < w;
    }

    template<typename T>
    void merge(std::vector<T>& a, std::vector<T>& aux, int lo, int mid, int hi)
    {
        for (int k = lo; k <= hi; ++k) {
            aux[k] = a[k];
        }

        // merge back to a[]
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; ++k) {
            if (i > mid) { a[k] = aux[j++]; }
            else if (j > hi) { a[k] = aux[i++]; }
            else if (less(aux[j], aux[i])) { a[k] = aux[j++]; }
            else { a[k] = aux[i++]; }
        }
    }
};

#endif // CLOSEST_PAIR_H
