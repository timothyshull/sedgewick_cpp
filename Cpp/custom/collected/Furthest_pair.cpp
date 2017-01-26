#include "Furthest_pair.h"

Furthest_pair::Furthest_pair(std::vector<Point_2d>& points)
{
    GrahamScan graham = new GrahamScan(points);

    // single point
    if (points.size() <= 1) return;

    // number of points on the hull
    int m = 0;
    for (Point_2d p : graham.hull())
        ++m;

    // the hull, _in counterclockwise order hull[1] to hull[m]
    std::vector<Point_2d> hull = new Point_2d[m + 1];
    m = 1;
    for (Point_2d p : graham.hull()) {
        hull[m++] = p;
    }
    m--;

    // all points are equal
    if (m == 1) return;

    // points are collinear
    if (m == 2) {
        best1 = hull[1];
        best2 = hull[2];
        bestDistanceSquared = best1.distance_squared_to(best2);
        return;
    }

    // k = farthest vertex from edge from hull[1] to hull[m]
    int k = 2;
    while (Point_2d.area2(hull[m], hull[1], hull[k + 1]) > Point_2d.area2(hull[m], hull[1], hull[k])) {
        ++k;
    }

    int j = k;
    for (int i{1}; i <= k && j <= m; ++i) {
        // Std_out::print_line("hull[i] + " and " + hull[j] + " are antipodal");
        if (hull[i].distance_squared_to(hull[j]) > bestDistanceSquared) {
            best1 = hull[i];
            best2 = hull[j];
            bestDistanceSquared = hull[i].distance_squared_to(hull[j]);
        }
        while ((j < m) && Point_2d.area2(hull[i], hull[i + 1], hull[j + 1]) > Point_2d.area2(hull[i], hull[i + 1], hull[j])) {
            ++j;
            // Std_out::print_line(hull[i] + " and " + hull[j] + " are antipodal");
            double distanceSquared = hull[i].distance_squared_to(hull[j]);
            if (distanceSquared > bestDistanceSquared) {
                best1 = hull[i];
                best2 = hull[j];
                bestDistanceSquared = hull[i].distance_squared_to(hull[j]);
            }
        }
    }
}

Point_2d Furthest_pair::either()
{
    return best1;
}

Point_2d Furthest_pair::other()
{
    return best2;
}

double Furthest_pair::distance()
{
    return std::sqrt(bestDistanceSquared);
}
