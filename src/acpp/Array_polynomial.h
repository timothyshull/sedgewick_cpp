#ifndef ARRAY_POLYNOMIAL_H
#define ARRAY_POLYNOMIAL_H

#include <vector>

template<typename Number_type>
class Array_polynomial {
private:
    // int _size;
    std::vector<Number_type> _coll;
    // Number_type* a;
public:
    Array_polynomial<Number_type>(Number_type c, std::size_t size) : _coll(size + 1, 0) { _coll[size] = c; }

    double eval(float x) const
    {
        double t{0.0};
        for (auto i = _coll.size() - 1; i >= 0; --i) {
            t = t * x + _coll[i];
        }
        return t;
    }

    friend Array_polynomial operator+(Array_polynomial& p, Array_polynomial& q)
    {
        Array_polynomial t{0, p._coll.size() > q._coll.size() ? p._coll.size() - 1 : q._coll.size() - 1};
        for (auto i = 0; i < p._coll.size(); ++i) {
            t._coll[i] += p._coll[i];
        }
        for (auto j = 0; j < q._coll.size(); ++j) {
            t._coll[j] += q._coll[j];
        }
        return t;
    }

    friend Array_polynomial operator*(Array_polynomial& p, Array_polynomial& q)
    {
        Array_polynomial t{0, (p._coll.size() - 1) + (q._coll.size() - 1)};
        for (auto i = 0; i < p._coll.size(); ++i) {
            for (auto j = 0; j < q._coll.size(); ++j) {
                t._coll[i + j] += p._coll[i] * q._coll[j];
            }
        }
        return t;
    }
};

#endif // ARRAY_POLYNOMIAL_H
