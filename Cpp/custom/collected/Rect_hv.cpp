#include "Rect_hv.h"

Rect_hv::Rect_hv(double xmin, double ymin, double xmax, double ymax)
{
    if (Double.isNaN(xmin) || Double.isNaN(xmax))
        throw new IllegalArgumentException("x-coordinate cannot be NaN");
    if (Double.isNaN(ymin) || Double.isNaN(ymax))
        throw new IllegalArgumentException("y-coordinates cannot be NaN");
    if (xmax < xmin || ymax < ymin) {
        throw new IllegalArgumentException("Invalid rectangle");
    }
    this.xmin = xmin;
    this.ymin = ymin;
    this.xmax = xmax;
    this.ymax = ymax;
}

double Rect_hv::xmin()
{
    return xmin;
}

double Rect_hv::xmax()
{
    return xmax;
}

double Rect_hv::ymin()
{
    return ymin;
}

double Rect_hv::ymax()
{
    return ymax;
}

double Rect_hv::width()
{
    return xmax - xmin;
}

double Rect_hv::height()
{
    return ymax - ymin;
}

bool Rect_hv::intersects(Rect_hv& that)
{
    return this.xmax >= that.xmin && this.ymax >= that.ymin
           && that.xmax >= this.xmin && that.ymax >= this.ymin;
}

bool Rect_hv::contains(Point_2d& p)
{
    return (p.x() >= xmin) && (p.x() <= xmax)
           && (p.y() >= ymin) && (p.y() <= ymax);
}

double Rect_hv::distanceTo(Point_2d& p)
{
    return Math.sqrt(this.distanceSquaredTo(p));
}

double Rect_hv::distanceSquaredTo(Point_2d& p)
{
    double dx = 0.0, dy = 0.0;
    if (p.x() < xmin) dx = p.x() - xmin;
    else if (p.x() > xmax) dx = p.x() - xmax;
    if (p.y() < ymin) dy = p.y() - ymin;
    else if (p.y() > ymax) dy = p.y() - ymax;
    return dx * dx + dy * dy;
}

bool Rect_hv::operator==(Rect_hv& rhs)
{
    if (other == this) return true;
    if (other == null) return false;
    if (other.getClass() != this.getClass()) return false;
    RectHV that = (RectHV) other;
    if (this.xmin != that.xmin) return false;
    if (this.ymin != that.ymin) return false;
    if (this.xmax != that.xmax) return false;
    if (this.ymax != that.ymax) return false;
    return true;
}

int Rect_hv::hashCode()
{
    int hash1 = ((Double) xmin).hashCode();
    int hash2 = ((Double) ymin).hashCode();
    int hash3 = ((Double) xmax).hashCode();
    int hash4 = ((Double) ymax).hashCode();
    return 31 * (31 * (31 * hash1 + hash2) + hash3) + hash4;
}

std::string Rect_hv::toString()
{
    return "[" + xmin + ", " + xmax + "] x [" + ymin + ", " + ymax + "]";
}

void Rect_hv::draw()
{
    StdDraw.line(xmin, ymin, xmax, ymin);
    StdDraw.line(xmax, ymin, xmax, ymax);
    StdDraw.line(xmax, ymax, xmin, ymax);
    StdDraw.line(xmin, ymax, xmin, ymin);
}
