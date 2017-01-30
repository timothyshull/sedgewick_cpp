#ifndef RECT_HV_H
#define RECT_HV_H

#include <cmath>

#include "Point_2d.h"

class Rect_hv {
public:
    Rect_hv(double x_min, double y_min, double x_max, double y_max);

    inline double x_min() const noexcept { return _x_min; }

    inline double x_max() const noexcept {return _x_max; }

    inline double y_min() const noexcept { return _y_min; }

    inline double y_max() const noexcept { return _y_max; }

    inline double width() const noexcept { return _x_max - _x_min; }

    inline double height() const noexcept { return _y_max - _y_min; }

    inline bool intersects(Rect_hv& rhs) const { return _x_max >= rhs._x_min && _y_max >= rhs._y_min && rhs._x_max >= _x_min && rhs._y_max >= _y_min; }

    inline bool contains(Point_2d& p) const noexcept { return (p.x() >= _x_min) && (p.x() <= _x_max) && (p.y() >= _y_min) && (p.y() <= _y_max); }

    inline double distance_to(Point_2d& p) const { return std::sqrt(distance_squared_to(p)); }

    double distance_squared_to(const Point_2d& p) const;

    bool operator==(const Rect_hv& rhs) const;

    std::size_t hash_code() const;

    std::string to_string() const;

    void draw();

private:
    const double _x_min;
    const double _y_min;
    const double _x_max;
    const double _y_max;
};

#endif // RECT_HV_H
