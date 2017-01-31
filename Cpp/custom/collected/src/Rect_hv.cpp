#include "Rect_hv.h"
#include "utility.h"
#include "Std_draw.h"

Rect_hv::Rect_hv(double x_min, double y_min, double x_max, double y_max)
        : _x_min{x_min},
          _x_max{x_max},
          _y_min{y_min},
          _y_max{y_max}
{
    if (std::isnan(x_min) || std::isnan(x_max)) {
        throw utility::Illegal_argument_exception("x-coordinate cannot be NaN");
    }
    if (std::isnan(y_min) || std::isnan(y_max)) {
        throw utility::Illegal_argument_exception("y-coordinates cannot be NaN");
    }
    if (x_max < x_min || y_max < y_min) {
        throw utility::Illegal_argument_exception("Invalid rectangle");
    }
}

double Rect_hv::distance_squared_to(const Point_2d& p) const
{
    double dx{0.0};
    double dy{0.0};
    if (p.x() < _x_min) { dx = p.x() - _x_min; }
    else if (p.x() > _x_max) { dx = p.x() - _x_max; }
    if (p.y() < _y_min) { dy = p.y() - _y_min; }
    else if (p.y() > _y_max) { dy = p.y() - _y_max; }
    return dx * dx + dy * dy;
}

bool Rect_hv::operator==(const Rect_hv& rhs) const
{
    return _x_min == rhs._x_min && _y_min == rhs._y_min && _x_max == rhs._x_max && _y_max == rhs._y_max;
}

std::size_t Rect_hv::hash_code() const
{
    auto hash = std::hash{};
    auto hash1 = hash(_x_min);
    auto hash2 = hash(_y_min);
    auto hash3 = hash(_x_max);
    auto hash4 = hash(_y_max);
    return 31 * (31 * (31 * hash1 + hash2) + hash3) + hash4;
}

std::string Rect_hv::to_string() const
{
    return "Rect_hv[" + std::to_string(_x_min) + ", " + std::to_string(_x_max) + "] x [" + std::to_string(_y_min) + ", " + std::to_string(_y_max) + "]";
}

void Rect_hv::draw()
{
    Std_draw::line(_x_min, _y_min, _x_max, _y_min);
    Std_draw::line(_x_max, _y_min, _x_max, _y_max);
    Std_draw::line(_x_max, _y_max, _x_min, _y_max);
    Std_draw::line(_x_min, _y_max, _x_min, _y_min);
}
