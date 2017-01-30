#include "Sparse_vector.h"
#include "utility.h"

Sparse_vector::Sparse_vector(int d) : _dimension{d}, _st{} {}

void Sparse_vector::put(int i, double value)
{
    if (i < 0 || i >= _dimension) { throw utility::Index_out_of_bounds_exception{"Illegal index"}; }
    if (value == 0.0) { _st.remove(i); }
    else { _st.put(i, value); }
}

double Sparse_vector::get(int i)
{
    if (i < 0 || i >= _dimension) { throw utility::Index_out_of_bounds_exception{"Illegal index"}; }
    if (_st.contains(i)) { return _st.get(i); }
    else { return 0.0; }
}

double Sparse_vector::dot(Sparse_vector that)
{
    if (_dimension != that._dimension) { throw utility::Illegal_argument_exception("Vector lengths disagree"); }
    double sum = 0.0;

    if (_st.size() <= that._st.size()) {
        for (int i : _st.keys()) {
            if (that._st.contains(i)) { sum += get(i) * that.get(i); }
        }
    } else {
        for (int i : that._st.keys()) {
            if (_st.contains(i)) { sum += get(i) * that.get(i); }
        }
    }
    return sum;
}

double Sparse_vector::dot(std::vector<double> that)
{
    double sum = 0.0;
    for (int i : _st.keys()) {
        sum += that[i] * get(i);
    }
    return sum;
}

double Sparse_vector::magnitude()
{
    return std::sqrt(dot(this));
}

double Sparse_vector::norm()
{
    return std::sqrt(dot(this));
}

Sparse_vector Sparse_vector::scale(double alpha)
{
    Sparse_vector c{_dimension};
    for (int i : _st.keys()) { c.put(i, alpha * get(i)); }
    return c;
}

Sparse_vector Sparse_vector::plus(Sparse_vector& that)
{
    if (_dimension != that._dimension) { throw utility::Illegal_argument_exception("Vector lengths disagree"); }
    Sparse_vector c{_dimension};
    for (int i : _st.keys()) { c.put(i, get(i)); }
    for (int i : that._st.keys()) { c.put(i, that.get(i) + c.get(i)); }
    return c;
}

std::string Sparse_vector::to_string()
{
    std::stringstream ss;
    ss << "Sparse_vector(\n";
    for (int i : _st.keys()) {
        ss << "    (" << i << ", " << _st.get(i) << "),\n";
    }
    return ss.str();
}
