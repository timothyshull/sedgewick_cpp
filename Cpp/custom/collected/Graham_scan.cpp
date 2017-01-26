#include "Graham_scan.h"

Graham_scan::Graham_scan(std::vector<Point_2d>& pts)
{
    int n = pts.length;
    std::vector<Point_2d>
    points = new Point_2d[n];
    for (int i{0}; i < n; ++i) {
        points[i] = pts[i];
    }

    // preprocess so that points[0] has lowest y-coordinate; break ties by x-coordinate
    // points[0] is an extreme point of the convex hull
    // (alternatively, could do easily _in linear time)
    Arrays.sort(points);

    // sort by polar angle with respect to base point points[0],
    // breaking ties by distance to points[0]
    Arrays.sort(points, 1, n, points[0].polarOrder());

    hull.push(points[0]);       // p[0] is first extreme point

    // find index k1 of first point not equal to points[0]
    int k1;
    for (k1 = 1; k1 < n; ++k1) {
        if (!points[0].equals(points[k1])) { break; }
    }
    if (k1 == n) { return; }        // all points equal

    // find index k2 of first point not collinear with points[0] and points[k1]
    int k2;
    for (k2 = k1 + 1; k2 < n; ++k2)
        if (Point_2d.ccw(points[0], points[k1], points[k2]) != 0) break;
    hull.push(points[k2 - 1]);    // points[k2-1] is second extreme point

    // Graham scan; note that points[_size-1] is extreme point different from points[0]
    for (int i{k2}; i < n; ++i) {
        Point_2d top = hull.pop();
        while (Point_2d.ccw(hull.peek(), top, points[i]) <= 0) {
            top = hull.pop();
        }
        hull.push(top);
        hull.push(points[i]);
    }

    assert isConvex();
}

std::vector<Point_2d> Graham_scan::hull()
{
    Stack<Point_2d> s = new Stack<Point_2d>();
    for (Point_2d p : hull) { s.push(p); }
    return s;
}

bool Graham_scan::isConvex()
{
    int n = hull.size();
    if (n <= 2) { return true; }

    std::vector<Point_2d>
    points = new Point_2d[n];
    int k = 0;
    for (Point_2d p : hull()) {
        points[k++] = p;
    }

    for (int i{0}; i < n; ++i) {
        if (Point_2d.ccw(points[i], points[(i + 1) % n], points[(i + 2) % n]) <= 0) {
            return false;
        }
    }
    return true;
}
