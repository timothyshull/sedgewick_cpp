#ifndef SPARSE_VECTOR_H
#define SPARSE_VECTOR_H

#include <map>
#include <vector>

class Sparse_vector {
public:

    Sparse_vector(int d);

    void put(int i, double value);

    double get(int i);

    int nnz();

    int size();

    int dimension();

    double dot(Sparse_vector that);

    double dot(std::vector<double> that);

    double magnitude();

    double norm();

    Sparse_vector scale(double alpha);

    Sparse_vector plus(Sparse_vector& that);

    std::string toString();

private:
    int d;
    std::map<int, double> st;
};

std::ostream& operator<<(std::ostream& os, Sparse_vector& out);

#endif // SPARSE_VECTOR_H
