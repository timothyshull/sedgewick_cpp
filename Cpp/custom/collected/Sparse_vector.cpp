#include "Sparse_vector.h"

Sparse_vector::Sparse_vector(int d)
{
    this.d = d;
    this.st = new ST<Integer, Double>();
}

void Sparse_vector::put(int i, double value)
{
    if (i < 0 || i >= d) { throw new IndexOutOfBoundsException("Illegal index"); }
    if (value == 0.0) { st. }
    delete (i);
    else st.put(i, value);
}

double Sparse_vector::get(int i)
{
    if (i < 0 || i >= d) { throw new IndexOutOfBoundsException("Illegal index"); }
    if (st.contains(i)) { return st.get(i); }
    else { return 0.0; }
}

int Sparse_vector::nnz()
{
    return st.size();
}

int Sparse_vector::size()
{
    return d;
}

int Sparse_vector::dimension()
{
    return d;
}

double Sparse_vector::dot(Sparse_vector that)
{
    if (this.d != that.d) { throw utility::Illegal_argument_exception("Vector lengths disagree"); }
    double sum = 0.0;

// iterate over the vector with the fewest nonzeros
    if (this.st.size() <= that.st.size()) {
        for (int i : this.st.keys()) {
            if (that.st.contains(i)) { sum += this.get(i) * that.get(i); }
        }
    } else {
        for (int i : that.st.keys()) {
            if (this.st.contains(i)) { sum += this.get(i) * that.get(i); }
        }
    }
    return sum;
}

double Sparse_vector::dot(std::vector<double> that)
{
    double sum = 0.0;
    for (int i : st.keys()) {
        sum += that[i] * this.get(i);
    }
    return sum;
}

double Sparse_vector::magnitude()
{
    return std::sqrt(this.dot(this));
}

double Sparse_vector::norm()
{
    return std::sqrt(this.dot(this));
}

Sparse_vector Sparse_vector::scale(double alpha)
{
    SparseVector c = new SparseVector(d);
    for (int i : this.st.keys()) { c.put(i, alpha * this.get(i)); }
    return c;
}

Sparse_vector Sparse_vector::plus(Sparse_vector& that)
{
    if (this.d != that.d) { throw utility::Illegal_argument_exception("Vector lengths disagree"); }
    SparseVector c = new SparseVector(d);
    for (int i : this.st.keys()) { c.put(i, this.get(i)); }                // c = this
    for (int i : that.st.keys()) c.put(i, that.get(i) + c.get(i));     // c = c + that
    return c;
}

std::string Sparse_vector::to_string()
{
    std::stringstream s = new std::stringstream();
    for (int i : st.keys()) {
        s.append("(" + i + ", " + st.get(i) + ") ");
    }
    return s.to_string();
}
