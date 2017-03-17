#include "Graham_scan.h"

Graham_scan::Graham_scan(std::vector<Point_2d>& pts)
{
    auto n = pts.size();
    std::vector<Point_2d> points{pts};

    std::sort(pts.begin(), pts.end());

    // TODO: check this
    std::sort(points.begin() + 1, points.end(), points[0].polar_order());

    _hull.push(points[0]);

    int k1;
    for (k1 = 1; k1 < n; ++k1) {
        if (points[0] != points[k1]) { break; }
    }
    if (k1 == n) { return; }

    int k2;
    for (k2 = k1 + 1; k2 < n; ++k2) {
        if (Point_2d::ccw(points[0], points[k1], points[k2]) != 0) { break; }
    }
    _hull.push(points[k2 - 1]);

    for (int i{k2}; i < n; ++i) {
        Point_2d top = _hull.pop();
        while (Point_2d::ccw(_hull.peek(), top, points[i]) <= 0) {
            top = _hull.pop();
        }
        _hull.push(top);
        _hull.push(points[i]);
    }

    utility::alg_assert(_is_convex(), "Graham_scan _is_convex check failed after construction");
}

Stack<Point_2d> Graham_scan::hull()
{
    Stack<Point_2d> s;
    for (Point_2d p : _hull) { s.push(p); }
    return s;
}

bool Graham_scan::_is_convex()
{
    auto n = _hull.size();
    if (n <= 2) { return true; }

    std::vector<Point_2d> points{n};
    int k = 0;
    for (Point_2d p : hull()) {
        points[k++] = p;
    }

    for (int i{0}; i < n; ++i) {
        if (Point_2d::ccw(points[i], points[(i + 1) % n], points[(i + 2) % n]) <= 0) {
            return false;
        }
    }
    return true;
}
