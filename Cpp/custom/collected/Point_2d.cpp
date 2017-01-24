#include "Point_2d.h"

bool X_order::operator<(Point_2d& lhs, Point_2d& rhs)
{
    if (p.x < q.x) return -1;
    if (p.x > q.x) return +1;
    return 0;
}

bool Y_order::operator<(Point_2d& lhs, Point_2d& rhs)
{
    if (p.y < q.y) return -1;
    if (p.y > q.y) return +1;
    return 0;
}

bool R_order::operator<(Point_2d& lhs, Point_2d& rhs)
{
    double delta = (p.x * p.x + p.y * p.y) - (q.x * q.x + q.y * q.y);
    if (delta < 0) return -1;
    if (delta > 0) return +1;
    return 0;
}

bool Atan_2_order::operator<(Point_2d& lhs, Point_2d& rhs)
{
    double angle1 = angleTo(q1);
    double angle2 = angleTo(q2);
    if (angle1 < angle2) return -1;
    else if (angle1 > angle2) return +1;
    else return 0;
}

bool Polar_order::operator<(Point_2d& lhs, Point_2d& rhs)
{
    double dx1 = q1.x - x;
    double dy1 = q1.y - y;
    double dx2 = q2.x - x;
    double dy2 = q2.y - y;

    if (dy1 >= 0 && dy2 < 0) return -1;    // q1 above; q2 below
    else if (dy2 >= 0 && dy1 < 0) return +1;    // q1 below; q2 above
    else if (dy1 == 0 && dy2 == 0) {            // 3-collinear and horizontal
        if (dx1 >= 0 && dx2 < 0) return -1;
        else if (dx2 >= 0 && dx1 < 0) return +1;
        else return 0;
    } else return -ccw(Point2D.this, q1, q2);
}

bool Distance_to_order::operator<(Point_2d& lhs, Point_2d& rhs)
{
    double dist1 = distanceSquaredTo(p);
    double dist2 = distanceSquaredTo(q);
    if (dist1 < dist2) return -1;
    else if (dist1 > dist2) return +1;
    else return 0;
}

Point_2d::Point_2d(double c, double y)
{
    if (Double.isInfinite(x) || Double.isInfinite(y))
        throw new IllegalArgumentException("Coordinates must be finite");
    if (Double.isNaN(x) || Double.isNaN(y))
        throw new IllegalArgumentException("Coordinates cannot be NaN");
    if (x == 0.0) this.x = 0.0;  // convert -0.0 to +0.0
    else this.x = x;

    if (y == 0.0) this.y = 0.0;  // convert -0.0 to +0.0
    else this.y = y;
}

double Point_2d::x()
{
    return x;
}

double Point_2d::y()
{
    return y;
}

double Point_2d::r()
{
    return Math.sqrt(x * x + y * y);
}

double Point_2d::theta()
{
    return Math.atan2(y, x);
}

double Point_2d::angleTo(Point_2d& that)
{
    double dx = that.x - this.x;
    double dy = that.y - this.y;
    return Math.atan2(dy, dx);
}

int Point_2d::ccw(Point_2d& a, Point_2d& b, Point_2d& c)
{
    double area2 = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area2 < 0) return -1;
    else if (area2 > 0) return +1;
    else return 0;
}

double Point_2d::area2(Point_2d& a, Point_2d& b, Point_2d& c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double Point_2d::distanceTo(Point_2d& that)
{
    double dx = this.x - that.x;
    double dy = this.y - that.y;
    return Math.sqrt(dx * dx + dy * dy);
}

double Point_2d::distanceSquaredTo(Point_2d& that)
{
    double dx = this.x - that.x;
    double dy = this.y - that.y;
    return dx * dx + dy * dy;
}

bool Point_2d::operator<(Point_2d& rhs)
{
    if (this.y < that.y) return -1;
    if (this.y > that.y) return +1;
    if (this.x < that.x) return -1;
    if (this.x > that.x) return +1;
    return 0;
}

bool Point_2d::operator==(Point_2d& rhs)
{
    if (other == this) return true;
    if (other == null) return false;
    if (other.getClass() != this.getClass()) return false;
    Point2D that = (Point2D) other;
    return this.x == that.x && this.y == that.y;
}

std::string Point_2d::toString()
{
    return "(" + x + ", " + y + ")";
}

int Point_2d::hashCode()
{
    int hashX = ((Double) x).hashCode();
    int hashY = ((Double) y).hashCode();
    return 31 * hashX + hashY;
}

void Point_2d::draw()
{
    StdDraw.point(x, y);
}

void Point_2d::drawTo() {
    StdDraw.line(this.x, this.y, that.x, that.y);
}

Polar_order Point_2d::polarOrder()
{
    return Polar_order{};
}

Atan_2_order Point_2d::atan2Order()
{
    return Atan_2_order{};
}

Distance_to_order Point_2d::distanceToOrder()
{
    return Distance_to_order{};
}
