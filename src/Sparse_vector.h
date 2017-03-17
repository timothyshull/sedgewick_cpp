#ifndef SPARSE_VECTOR_H
#define SPARSE_VECTOR_H

#include <map>
#include <vector>
#include "Symbol_table.h"

class Sparse_vector {
public:

    Sparse_vector(int d);

    void put(int i, double value);

    double get(int i);

    inline int nnz() const { return static_cast<int>(_st.size()); }

    inline int size() const noexcept { return _dimension; }

    inline int dimension() const noexcept { return _dimension; }

    double dot(Sparse_vector that);

    double dot(std::vector<double> that);

    double magnitude();

    double norm();

    Sparse_vector scale(double alpha);

    Sparse_vector plus(Sparse_vector& that);

    std::string to_string();

private:
    int _dimension;
    Symbol_table<int, double> _st;
};

std::ostream& operator<<(std::ostream& os, Sparse_vector& out);

#endif // SPARSE_VECTOR_H
