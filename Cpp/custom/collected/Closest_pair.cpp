#include "Closest_pair.h"

Closest_pair::Closest_pair(std::vector<Point_2d>& points)
{
    int n = points.length;
    if (n <= 1) { return; }

    // sort by x-coordinate (breaking ties by y-coordinate)
    std::vector<Point_2d>
    pointsByX = new Point_2d[n];
    for (int i{0}; i < n; ++i) {
        pointsByX[i] = points[i];
    }
    Arrays.sort(pointsByX, Point_2d.X_ORDER);

    // _check for coincident points
    for (int i{0}; i < n - 1; ++i) {
        if (pointsByX[i].equals(pointsByX[i + 1])) {
            bestDistance = 0.0;
            best1 = pointsByX[i];
            best2 = pointsByX[i + 1];
            return;
        }
    }

    // sort by y-coordinate (but not yet sorted)
    std::vector<Point_2d>
    pointsByY = new Point_2d[n];
    for (int i{0}; i < n; ++i) {
        pointsByY[i] = pointsByX[i];
    }

    // auxiliary array
    std::vector<Point_2d>
    aux = new Point_2d[n];

    closest(pointsByX, pointsByY, aux, 0, n - 1);
}

double Closest_pair::closest(std::vector<Point_2d>& pointsByX, std::vector<Point_2d>& pointsByY, std::vector<Point_2d>& aux, int lo, int hi)
{
    if (hi <= lo) { return Double.POSITIVE_INFINITY; }

    int mid = lo + (hi - lo) / 2;
    Point_2d median = pointsByX[mid];

    // compute closest pair with both endpoints in left subarray or both in right subarray
    double delta1 = closest(pointsByX, pointsByY, aux, lo, mid);
    double delta2 = closest(pointsByX, pointsByY, aux, mid + 1, hi);
    double delta = std::min(delta1, delta2);

    // merge back so that pointsByY[lo..hi] are sorted by y-coordinate
    merge(pointsByY, aux, lo, mid, hi);

    // aux[0..m-1] = sequence of points closer than delta, sorted by y-coordinate
    int m = 0;
    for (int i{lo}; i <= hi; ++i) {
        if (std::abs(pointsByY[i].x() - median.x()) < delta) {
            aux[m++] = pointsByY[i];
        }
    }

    // compare each point to its neighbors with y-coordinate closer than delta
    for (int i{0}; i < m; ++i) {
        // a geometric packing argument shows that this loop iterates at most 7 times
        for (int j{i + 1}; (j < m) && (aux[j].y() - aux[i].y() < delta); ++j) {
            double distance = aux[i].distanceTo(aux[j]);
            if (distance < delta) {
                delta = distance;
                if (distance < bestDistance) {
                    bestDistance = delta;
                    best1 = aux[i];
                    best2 = aux[j];
                    // Std_out::print_line("better distance = " + delta + " from " + best1 + " to " + best2);
                }
            }
        }
    }
    return delta;
}

Point_2d Closest_pair::either()
{
    return best1;
}

Point_2d Closest_pair::other()
{
    return best2;
}

double Closest_pair::distance()
{
    return bestDistance;
}
