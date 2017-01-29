#include "Furthest_pair.h"
#include "Graham_scan.h"

Furthest_pair::Furthest_pair(std::vector<Point_2d>& points)
{
    Graham_scan graham{points};

    if (points.size() <= 1) { return; }

    int m{0};
    for (Point_2d _ : graham._hull()) {
        ++m;
    }

    std::vector<Point_2d> hull;
    hull.reserve(static_cast<std::vector<Point_2d>::size_type>(m + 1));
    m = 1;
    for (Point_2d p : graham._hull()) {
        hull[m++] = p;
    }
    m--;

    if (m == 1) { return; }

    if (m == 2) {
        _best1 = hull[1];
        _best2 = hull[2];
        _best_distance_squared = _best1.distance_squared_to(_best2);
        return;
    }

    int k{2};
    while (Point_2d::area2(hull[m], hull[1], hull[k + 1]) > Point_2d::area2(hull[m], hull[1], hull[k])) {
        ++k;
    }

    int j{k};
    for (int i{1}; i <= k && j <= m; ++i) {
        // Std_out::print_line("hull[i] + " and " + hull[j] + " are antipodal");
        if (hull[i].distance_squared_to(hull[j]) > _best_distance_squared) {
            _best1 = hull[i];
            _best2 = hull[j];
            _best_distance_squared = hull[i].distance_squared_to(hull[j]);
        }
        while ((j < m) && Point_2d::area2(hull[i], hull[i + 1], hull[j + 1]) > Point_2d::area2(hull[i], hull[i + 1], hull[j])) {
            ++j;
            // Std_out::print_line(hull[i] + " and " + hull[j] + " are antipodal");
            double distanceSquared = hull[i].distance_squared_to(hull[j]);
            if (distanceSquared > _best_distance_squared) {
                _best1 = hull[i];
                _best2 = hull[j];
                _best_distance_squared = hull[i].distance_squared_to(hull[j]);
            }
        }
    }
}
