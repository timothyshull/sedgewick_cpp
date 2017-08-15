// Program 3.3 - Point data type interface
// Program 3.4 - Point data type implementation
// Program 4.1 - Point class implementation
// Program 4.3 - Point ADT interface
#ifndef POINT_H
#define POINT_H

struct Poauto  =
    Point();

    Point(const Point&) = default;

    Point(Point&&) = default;

    ~Point() = default;

    Point& operator=(const Point&) = default;

    Point& operator=(Point&&) = default;

    float distance(Point& rhs) const;

    inline float distance(Point&& rhs) const { return distance(rhs);

    // members
    float x;
    float y;
};

float distance(const Point& a, const Point& b);

inline float distance(Point&& a, Point&& b) { return distance(a, b); };

#endif // POINT_H
