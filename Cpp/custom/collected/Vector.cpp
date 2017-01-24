#include "Vector.h"

Vector::Vector(int d)
{
    this.d = d;
    data = new double[d];
}

Vector::Vector(std::initializer_list<double>& a)
{
    d = a.length;

    // defensive copy so that client can't alter our copy of data[]
    data = new double[d];
    for (int i = 0; i < d; i++)
        data[i] = a[i];
}

int Vector::length()
{
    return d;
}

int Vector::dimension()
{
    return d;
}

double Vector::dot(Vector& that)
{
    if (this.d != that.d) throw new IllegalArgumentException("Dimensions don't agree");
    double sum = 0.0;
    for (int i = 0; i < d; i++)
        sum = sum + (this.data[i] * that.data[i]);
    return sum;
}

double Vector::magnitude()
{
    return Math.sqrt(this.dot(this));
}

double Vector::distanceTo(Vector& that)
{
    if (this.d != that.d) throw new IllegalArgumentException("Dimensions don't agree");
    return this.minus(that).magnitude();
}

Vector Vector::plus(Vector& that)
{
    if (this.d != that.d) throw new IllegalArgumentException("Dimensions don't agree");
    Vector c = new Vector(d);
    for (int i = 0; i < d; i++)
        c.data[i] = this.data[i] + that.data[i];
    return c;
}

Vector Vector::minus(Vector& that) {
    if (this.d != that.d) throw new IllegalArgumentException("Dimensions don't agree");
    Vector c = new Vector(d);
    for (int i = 0; i < d; i++)
        c.data[i] = this.data[i] - that.data[i];
    return c;
}

double Vector::cartesian(int i)
{
    return data[i];
}

Vector Vector::times(double alpha)
{
    Vector c = new Vector(d);
    for (int i = 0; i < d; i++)
        c.data[i] = alpha * data[i];
    return c;
}

Vector Vector::scale(double alpha)
{
    Vector c = new Vector(d);
    for (int i = 0; i < d; i++)
        c.data[i] = alpha * data[i];
    return c;
}

Vector Vector::direction()
{
    if (this.magnitude() == 0.0) throw new ArithmeticException("Zero-vector has no direction");
    return this.times(1.0 / this.magnitude());
}

std::string Vector::toString()
{
    StringBuilder s = new StringBuilder();
    for (int i = 0; i < d; i++)
        s.append(data[i] + " ");
    return s.toString();
}

std::ostream& operator<<(std::ostream& os, Vector& out)
{
    return os << out.toString();
}
