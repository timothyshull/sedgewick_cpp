#ifndef POINT_2D_H
#define POINT_2D_H

#include <string>

class Point_2d;

struct X_order {
    bool operator<(Point_2d& lhs, Point_2d& rhs);
};

struct Y_order {
    bool operator<(Point_2d& lhs, Point_2d& rhs);
};

struct R_order {
    bool operator<(Point_2d& lhs, Point_2d& rhs);
};

struct Atan_2_order {
    bool operator<(Point_2d& lhs, Point_2d& rhs);
};

struct Polar_order {
    bool operator<(Point_2d& lhs, Point_2d& rhs);
};

struct Distance_to_order {
    bool operator<(Point_2d& lhs, Point_2d& rhs);
};

class Point_2d {
public:
    const static X_order X_ORDER = X_order{};
    const static Y_order Y_ORDER = Y_order{};
    const static R_order R_ORDER = R_order{};

    Point_2d(double c, double y);

    double x();

    double y();

    double r();

    double theta();

    double angleTo(Point_2d& that);

    int ccw(Point_2d& a, Point_2d& b, Point_2d& c);

    double area2(Point_2d& a, Point_2d& b, Point_2d& c);

    double distanceTo(Point_2d& that);

    double distanceSquaredTo(Point_2d& that);

    bool operator<(Point_2d& rhs);

    bool operator==(Point_2d& rhs);

    std::string toString();

    int hashCode();

    void draw();

    void drawTo(Point_2d& that);

    Polar_order polarOrder();

    Atan_2_order atan2Order();

    Distance_to_order distanceToOrder();

private:
    const double x;
    const double y;
};

#endif // POINT_2D_H
