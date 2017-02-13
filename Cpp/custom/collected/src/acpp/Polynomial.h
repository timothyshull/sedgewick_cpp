// Program 4.24 - ADT interface for polynomials
// Program 4.25 - Array implementation of polynomial ADT
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <ostream>
#include <vector>
#include <sstream>

template<typename Number_type>
class Polynomial {
public:
    Polynomial<Number_type>(Number_type c, std::size_t size)
            : _numbers{}
    {
        _numbers.reserve(size + 1);
        _numbers[size] = c;
        for (int i{0}; i < size; ++i) { _numbers[i] = 0; }
    }

    inline std::size_t size() const noexcept { return _numbers.size(); }

    double eval(double x) const
    {
        double t{0.0};
        for (auto i = _numbers.size() - 1; i >= 0; --i) {
            t = t * x + _numbers[i];
        }
        return t;
    }

    friend Polynomial operator+(Polynomial& lhs, Polynomial& rhs)
    {
        Polynomial t{0, lhs.size() > rhs.size() ? lhs.size() - 1 : rhs.size() - 1};
        for (int i{0}; i < lhs.size(); ++i) {
            t._numbers[i] += lhs._numbers[i];
        }
        for (int j{0}; j < rhs.size(); ++j) {
            t._numbers[j] += rhs._numbers[j];
        }
        return t;
    }

    friend Polynomial operator*(Polynomial& p, Polynomial& q)
    {
        Polynomial t{0, (p.size() - 1) + (q.size() - 1)};
        for (int i{0}; i < p.size(); ++i) {
            for (int j{0}; j < q.size(); ++j) {
                t._numbers[i + j] += p._numbers[i] * q._numbers[j];
            }
        }
        return t;
    }

    std::string to_string()
    {
        std::stringstream ss;
        ss << "Polynomial(\n";
        for (auto t : _numbers) {
            ss << "    " << t << "\n";
        }
        ss << ")";
        return ss.str();
    }

private:
    std::vector<Number_type> _numbers;
};

template<typename Number_type>
std::ostream& operator<<(std::ostream& os, Polynomial<Number_type>& rhs)
{
    return os << rhs.to_string() << "\n";
}

template<typename Number_type>
std::ostream& operator<<(std::ostream& os, Polynomial<Number_type>&& rhs)
{
    return os << rhs.to_string() << "\n";
}

#endif // POLYNOMIAL_H
