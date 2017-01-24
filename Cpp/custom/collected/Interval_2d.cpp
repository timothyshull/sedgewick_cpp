#include "Interval_2d.h"

Interval_2d::Interval_2d(Interval_1d& x, Interval_1d& y)
{
    this.x = x;
    this.y = y;
}

bool Interval_2d::intersects(Interval_2d& that)
{
    if (!this.x.intersects(that.x)) { return false; }
    if (!this.y.intersects(that.y)) { return false; }
    return true;
}

bool Interval_2d::contains(Point_2d& that)
{
    return x.contains(p.x()) && y.contains(p.y());
}

double Interval_2d::area()
{
    return x.length() * y.length();
}

std::string Interval_2d::to_string()
{
    return x + " x " + y;
}

bool Interval_2d::operator==(Interval_2d& rhs)
{
    if (other == this) { return true; }
    if (other == null) { return false; }
    if (other.getClass() != this.getClass()) { return false; }
    Interval2D that = (Interval2D) other;
    return this.x.equals(that.x) && this.y.equals(that.y);
}

int Interval_2d::hashCode()
{
    int hash1 = x.hashCode();
    int hash2 = y.hashCode();
    return 31 * hash1 + hash2;
}

void Interval_2d::draw()
{
    double xc = (x.min() + x.max()) / 2.0;
    double yc = (y.min() + y.max()) / 2.0;
    Std_draw::rectangle(xc, yc, x.length() / 2.0, y.length() / 2.0);
}
