#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class Vector {
public:
    Vector(int d);

    Vector(std::initializer_list<double>& a);

    int length();

    int dimension();

    double dot(Vector& that);

    double magnitude();

    double distanceTo(Vector& that);

    Vector plus(Vector& that);

    double cartesian(int i);

    Vector times(double alpha);

    Vector scale(double alpha);

    Vector direction();

    std::string toString();

private:
    int d;
    std::vector<double> data;
};

std::ostream& operator<<(std::ostream& os, Vector& out);

#endif // VECTOR_H
