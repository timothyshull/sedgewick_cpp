#ifndef RECT_HV_H
#define RECT_HV_H

#include "Point_2d.h"

class Rect_hv {
public:
    Rect_hv(double xmin, double ymin, double xmax, double ymax);

    double xmin();

    double xmax();

    double ymin();

    double ymax();

    double width();

    double height();

    bool intersects(Rect_hv& that);

    bool contains(Point_2d& p);

    double distanceTo(Point_2d& p);

    double distanceSquaredTo(Point_2d& p);

    bool operator==(Rect_hv& rhs);

    int hashCode();

    std::string to_string();

    void draw();

private:
    const double xmin;
    const double ymin;
    const double xmax;
    const double ymax;
};

#endif // RECT_HV_H
