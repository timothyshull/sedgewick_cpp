#include "Interval_2d.h"
#include "Std_draw.h"

Interval_2d::Interval_2d(const Interval_1d& x, const Interval_1d& y) : _x{x}, _y{y} {}

bool Interval_2d::intersects(const Interval_2d& rhs) const
{
    if (!_x.intersects(rhs._x)) { return false; }
    return _y.intersects(rhs._y);
}

bool Interval_2d::contains(const Point_2d& rhs) const
{
    return _x.contains(rhs.x()) && _y.contains(rhs.y());
}

double Interval_2d::area() const
{
    return _x.length() * _y.length();
}

std::string Interval_2d::to_string() const
{
    return "Interval_2d(x: " + _x.to_string() + ", y " + _y.to_string() + ")";
}

bool Interval_2d::operator==(const Interval_2d& rhs) const
{
    return _x == rhs._x && _y == rhs._y;
}

std::size_t Interval_2d::hash_code() const
{
    std::size_t hash1{_x.hash_code()};
    std::size_t hash2{_y.hash_code()};
    return 31 * hash1 + hash2;
}

void Interval_2d::draw() const
{
    double xc{(_x.min() + _x.max()) / 2.0};
    double yc{(_y.min() + _y.max()) / 2.0};
    Std_draw::rectangle(xc, yc, _x.length() / 2.0, _y.length() / 2.0);
}
