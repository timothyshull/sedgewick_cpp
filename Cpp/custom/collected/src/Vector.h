#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class Vector {
public:
    Vector() = default;

    Vector(const Vector&) = default;

    Vector(Vector&&) = default;

    ~Vector() = default;

    Vector& operator=(const Vector&) = default;

    Vector& operator=(Vector&&) = default;

    Vector(int d);

    Vector(std::initializer_list<double>& a);

    inline int length() const noexcept { return _dimension; }

    inline int dimension() const noexcept { return _dimension; }

    double dot(Vector& that);

    double magnitude();

    double distance_to(Vector& rhs);

    Vector plus(Vector& rhs);

    Vector minus(Vector& rhs);

    inline double cartesian(int i) const { return _data[i]; }

    Vector times(double alpha);

    Vector scale(double alpha);

    Vector direction();

    std::string to_string();

private:
    int _dimension;
    std::vector<double> _data;
};

std::ostream& operator<<(std::ostream& os, Vector& out);

#endif // VECTOR_H
