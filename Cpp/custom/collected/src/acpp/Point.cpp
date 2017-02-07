// Program 3.3 - Point data type interface
// Program 3.4 - Point data type implementation
// Program 4.1 - Point class implementation
// Program 4.3 - Point ADT interface
#include <cmath>
#include <random>

#include "Point.h"

std::random_device rd;
std::default_random_engine gen{rd()};

Point::Point() : x{std::generate_canonical<float, 10>(gen)}, y{std::generate_canonical<float, 10>(gen)} {}

float Point::distance(Point& rhs) const
{
    float dx{x - rhs.x};
    float dy{y - rhs.y};
    return std::sqrtf(dx * dx + dy * dy);
}

float distance(const Point& a, const Point& b)
{
    float dx{a.x - b.x};
    float dy{a.y - b.y};
    return std::sqrtf(dx * dx + dy * dy);
}
