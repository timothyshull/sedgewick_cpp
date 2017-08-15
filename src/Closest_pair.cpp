#include <cmath>
#include "Closest_pair.h"
#include "utility.h"

// TODO: make sure this does not break the code
Closest_pair::Closest_pair(std::vector<Point_2d>& points)
        : _best1{points[0]},
          _best2{points[1]}
{
    auto n = points.size();
    // will have thrown already
    if (n <= 1) { throw utility::Illegal_argument_exception{"There must be at least two points passed to construct a Closest_pair"}; }

    std::vector<Point_2d> points_by_x;
    points_by_x.reserve(n);
    for (auto i = 0; i < n; ++i) {
        points_by_x[i] = points[i];
    }
    std::sort(points_by_x.begin(), points_by_x.end(), Point_2d::x_order);

    for (auto i = 0; i < n - 1; ++i) {
        if (points_by_x[i] == points_by_x[i + 1]) {
            _best_distance = 0.0;
            _best1 = points_by_x[i];
            _best2 = points_by_x[i + 1];
            return;
        }
    }

    std::vector<Point_2d> points_by_y;
    points_by_y.reserve(n);
    for (auto i = 0; i < n; ++i) {
        points_by_y[i] = points_by_x[i];
    }

    std::vector<Point_2d> aux;
    aux.reserve(n);

    closest(points_by_x, points_by_y, aux, 0, static_cast<int>(n - 1));
}

double Closest_pair::closest(std::vector<Point_2d>& points_by_x, std::vector<Point_2d>& points_by_y, std::vector<Point_2d>& aux, int lo, int hi)
{
    if (hi <= lo) { return std::numeric_limits<double>::infinity(); }

    int mid = lo + (hi - lo) / 2;
    Point_2d median = points_by_x[mid];

    double delta1{closest(points_by_x, points_by_y, aux, lo, mid)};
    double delta2{closest(points_by_x, points_by_y, aux, mid + 1, hi)};
    double delta{std::min(delta1, delta2)};

    merge(points_by_y, aux, lo, mid, hi);

    int m = 0;
    for (auto i = lo; i <= hi; ++i) {
        if (std::abs(points_by_y[i].x() - median.x()) < delta) {
            aux[m++] = points_by_y[i];
        }
    }

    for (auto i = 0; i < m; ++i) {
        for (auto j = i + 1; (j < m) && (aux[j].y() - aux[i].y() < delta); ++j) {
            double distance{aux[i].distance_to(aux[j])};
            if (distance < delta) {
                delta = distance;
                if (distance < _best_distance) {
                    _best_distance = delta;
                    _best1 = aux[i];
                    _best2 = aux[j];
                    // Std_out::print_line("better distance = " + delta + " from " + best1 + " to " + best2);
                }
            }
        }
    }
    return delta;
}
