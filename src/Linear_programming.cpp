#include "Linear_programming.h"
#include "Std_out.h"
#include "utility.h"

Linear_programming::Linear_programming(std::vector<std::vector<double>>& a, std::vector<double>& b, std::vector<double>& c)
        : _m{static_cast<int>(b.size())},
          _n{static_cast<int>(c.size())},
          _aux(static_cast<std::vector<std::vector<double>>::size_type>(_m + 1)),
          _basis(static_cast<std::vector<int>::size_type>(_m))
{
    for (auto i = 0; i < _m; ++i) {
        if (b[i] < 0) { throw utility::Illegal_argument_exception{"RHS must be nonnegative"}; }
    }

    for (auto v : _aux) {
        v.reserve(static_cast<std::vector<double>::size_type>(_n + _m + 1));
    }

    for (auto i = 0; i < _m; ++i) {
        for (auto j = 0; j < _n; ++j) {
            _aux[i][j] = a[i][j];
        }
    }
    for (auto i = 0; i < _m; ++i) {
        _aux[i][_n + i] = 1.0;
    }
    for (auto j = 0; j < _n; ++j) {
        _aux[_m][j] = c[j];
    }
    for (auto i = 0; i < _m; ++i) {
        _aux[i][_m + _n] = b[i];
    }

    for (auto i = 0; i < _m; ++i) {
        _basis[i] = _n + i;
    }

    solve();

    utility::alg_assert(_check(a, b, c), "Linear_programming invariant check failed after construction");
}

void Linear_programming::solve()
{
    int p;
    int q;
    while (true) {

        q = bland();
        if (q == -1) { break; }

        p = min_ratio_rule(q);
        if (p == -1) { throw utility::Arithmetic_exception{"Linear program is unbounded"}; }

        pivot(p, q);

        _basis[p] = q;
    }
}

int Linear_programming::bland()
{
    for (auto j = 0; j < _m + _n; ++j) {
        if (_aux[_m][j] > 0) { return j; }
    }
    return -1;
}

int Linear_programming::dantzig()
{
    auto q = 0;
    for (auto j = 1; j < _m + _n; ++j) {
        if (_aux[_m][j] > _aux[_m][q]) { q = j; }
    }

    if (_aux[_m][q] <= 0) {
        return -1;
    } else { return q; }
}

int Linear_programming::min_ratio_rule(int q)
{
    int p = -1;
    for (auto i = 0; i < _m; ++i) {
        if (_aux[i][q] <= _epsilon) { continue; }
        else if (p == -1) { p = i; }
        else if ((_aux[i][_m + _n] / _aux[i][q]) < (_aux[p][_m + _n] / _aux[p][q])) { p = i; }
    }
    return p;
}

void Linear_programming::pivot(int p, int q)
{
    for (auto i = 0; i <= _m; ++i) {
        for (auto j = 0; j <= _m + _n; ++j) {
            if (i != p && j != q) { _aux[i][j] -= _aux[p][j] * _aux[i][q] / _aux[p][q]; }
        }
    }

    for (auto i = 0; i <= _m; ++i) {
        if (i != p) { _aux[i][q] = 0.0; }
    }

    for (auto j = 0; j <= _m + _n; ++j) {
        if (j != q) { _aux[p][j] /= _aux[p][q]; }
    }
    _aux[p][q] = 1.0;
}

double Linear_programming::value()
{
    return -_aux[_m][_m + _n];
}

std::vector<double> Linear_programming::primal()
{
    std::vector<double> x;
    x.reserve(static_cast<std::vector<double>::size_type>(_n));
    for (auto i = 0; i < _m; ++i) {
        if (_basis[i] < _n) { x[_basis[i]] = _aux[i][_m + _n]; }
    }
    return x;
}

std::vector<double> Linear_programming::dual()
{
    std::vector<double> y;
    y.reserve(static_cast<std::vector<double>::size_type>(_m));
    for (auto i = 0; i < _m; ++i) {
        y[i] = -_aux[_m][_n + i];
    }
    return y;
}

bool Linear_programming::_is_primal_feasible(std::vector<std::vector<double>>& a, std::vector<double>& b)
{
    std::vector<double> x{primal()};

    for (auto j = 0; j < x.size(); ++j) {
        if (x[j] < 0.0) {
            Std_out::print_line("x[" + std::to_string(j) + "] = " + std::to_string(x[j]) + " is negative");
            return false;
        }
    }

    for (auto i = 0; i < _m; ++i) {
        double sum = 0.0;
        for (auto j = 0; j < _n; ++j) {
            sum += a[i][j] * x[j];
        }
        if (sum > b[i] + _epsilon) {
            Std_out::print_line("not primal feasible");
            Std_out::print_line("b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + ", sum = " + std::to_string(sum));
            return false;
        }
    }
    return true;
}

bool Linear_programming::_is_dual_feasible(std::vector<std::vector<double>>& A, std::vector<double>& c)
{
    std::vector<double> y = dual();

    for (auto i = 0; i < y.size(); ++i) {
        if (y[i] < 0.0) {
            Std_out::print_line("y[" + std::to_string(i) + "] = " + std::to_string(y[i]) + " is negative");
            return false;
        }
    }

    double sum;
    for (auto j = 0; j < _n; ++j) {
        sum = 0.0;
        for (auto i = 0; i < _m; ++i) {
            sum += A[i][j] * y[i];
        }
        if (sum < c[j] - _epsilon) {
            Std_out::print_line("not dual feasible");
            Std_out::print_line("c[" + std::to_string(j) + "] = " + std::to_string(c[j]) + ", sum = " + std::to_string(sum));
            return false;
        }
    }
    return true;
}

bool Linear_programming::_is_optimal(std::vector<double>& b, std::vector<double>& c)
{
    std::vector<double> x{primal()};
    std::vector<double> y{dual()};
    double val{value()};

    double value1{0.0};
    for (auto j = 0; j < x.size(); ++j) {
        value1 += c[j] * x[j];
    }
    double value2{0.0};
    for (auto i = 0; i < y.size(); ++i) {
        value2 += y[i] * b[i];
    }
    if (std::abs(val - value1) > _epsilon || std::abs(val - value2) > _epsilon) {
        Std_out::print_line("value = " + std::to_string(val) + ", cx = " + std::to_string(value1) + ", yb = " + std::to_string(value2));
        return false;
    }

    return true;
}

bool Linear_programming::_check(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& c)
{
    return _is_primal_feasible(A, b) && _is_dual_feasible(A, c) && _is_optimal(b, c);
}

void Linear_programming::_show()
{
    Std_out::print_line("m = " + _m);
    Std_out::print_line("_size = " + _n);
    for (auto i = 0; i <= _m; ++i) {
        for (auto j = 0; j <= _m + _n; ++j) {
            Std_out::printf("%7.2f ", _aux[i][j]);
            // Std_out::printf("%10.7f ", a[i][j]);
        }
        Std_out::print_line();
    }
    Std_out::print_line("value = " + std::to_string(value()));
    for (auto i = 0; i < _m; ++i) {
        if (_basis[i] < _n) { Std_out::print_line("x_" + std::to_string(_basis[i]) + " = " + std::to_string(_aux[i][_m + _n])); }
    }
    Std_out::print_line();
}

void Lp_tests::test(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& c)
{
    Linear_programming lp{A, b, c};
    Std_out::print_line("value = " + std::to_string(lp.value()));
    std::vector<double> x{lp.primal()};
    for (auto i = 0; i < x.size(); ++i) {
        Std_out::print_line("x[" + std::to_string(i) + "] = " + std::to_string(x[i]));
    }
    std::vector<double> y{lp.dual()};
    for (auto j = 0; j < y.size(); ++j) {
        Std_out::print_line("y[" + std::to_string(j) + "] = " + std::to_string(y[j]));
    }
}

void Lp_tests::test1()
{
    std::vector<std::vector<double>> A = {
            {-1, 1,  0},
            {1,  4,  0},
            {2,  1,  0},
            {3,  -4, 0},
            {0,  0,  1},
    };
    std::vector<double> c = {1, 1, 1};
    std::vector<double> b = {5, 45, 27, 24, 4};
    test(A, b, c);
}

void Lp_tests::test2()
{
    std::vector<double> c = {13.0, 23.0};
    std::vector<double> b = {480.0, 160.0, 1190.0};
    std::vector<std::vector<double>> A = {
            {5.0,  15.0},
            {4.0,  4.0},
            {35.0, 20.0},
    };
    test(A, b, c);
}

void Lp_tests::test3()
{
    std::vector<double> c = {2.0, 3.0, -1.0, -12.0};
    std::vector<double> b = {3.0, 2.0};
    std::vector<std::vector<double>> A = {
            {-2.0, -9.0, 1.0,  9.0},
            {1.0,  1.0,  -1.0, -2.0},
    };
    test(A, b, c);
}

void Lp_tests::test4()
{
    std::vector<double> c = {10.0, -57.0, -9.0, -24.0};
    std::vector<double> b = {0.0, 0.0, 1.0};
    std::vector<std::vector<double>> A = {
            {0.5, -5.5, -2.5, 9.0},
            {0.5, -1.5, -0.5, 1.0},
            {1.0, 0.0,  0.0,  0.0},
    };
    test(A, b, c);
}
