#include "Interval_1d.h"

bool Min_endpoint_comparator::operator()(Interval_1d& a, Interval_1d& b)
{
    if (a.min < b.min) { return -1; }
    else if (a.min > b.min) { return +1; }
    else if (a.max < b.max) { return -1; }
    else if (a.max > b.max) { return +1; }
    else { return 0; }
}

bool Max_endpoint_comparator::operator()(Interval_1d& a, Interval_1d& b)
{
    if (a.min < b.max) { return -1; }
    else if (a.min > b.max) { return +1; }
    else if (a.min < b.min) { return -1; }
    else if (a.min > b.min) { return +1; }
    else { return 0; }
}

bool Length_comparator::operator()(Interval_1d& a, Interval_1d& b)
{
    double alen = a.length();
    double blen = b.length();
    if (alen < blen) { return -1; }
    else if (alen > blen) { return +1; }
    else { return 0; }
}

Interval_1d::Interval_1d(double min, double max)
{
    if (Double.isInfinite(min) || Double.isInfinite(max)) {
        throw new IllegalArgumentException("Endpoints must be finite");
    }
    if (Double.isNaN(min) || Double.isNaN(max)) {
        throw new IllegalArgumentException("Endpoints cannot be NaN");
    }

    // convert -0.0 to +0.0
    if (min == 0.0) { min = 0.0; }
    if (max == 0.0) { max = 0.0; }

    if (min <= max) {
        this.min = min;
        this.max = max;
    } else { throw new IllegalArgumentException("Illegal interval"); }
}

double Interval_1d::left()
{
    return min;
}

double Interval_1d::right()
{
    return max;
}

double Interval_1d::min()
{
    return min;
}

double Interval_1d::max()
{
    return max;
}

bool Interval_1d::intersects(Interval_1d& that)
{
    if (this.max < that.min) { return false; }
    if (that.max < this.min) { return false; }
    return true;
}

bool Interval_1d::contains(double x)
{
    return (min <= x) && (x <= max);
}

double Interval_1d::length()
{
    return max - min;
}

std::string Interval_1d::to_string()
{
    return "[" + min + ", " + max + "]";
}

bool Interval_1d::operator==(Interval_1d& rhs)
{
    if (other == this) { return true; }
    if (other == null) { return false; }
    if (other.getClass() != this.getClass()) { return false; }
    Interval1D that = (Interval1D) other;
    return this.min == that.min && this.max == that.max;
}

int Interval_1d::hashCode()
{
    int hash1 = ((Double) min).hashCode();
    int hash2 = ((Double) max).hashCode();
    return 31 * hash1 + hash2;
}

std::ostream& operator<<(std::ostream& os, Interval_1d& out)
{
    return os << out.to_string();
}
