#include "Gauss_jordan_elimination.h"
#include "utility.h"
#include "Std_out.h"

Gauss_jordan_elimination::Gauss_jordan_elimination(std::vector<std::vector<double>>& a, std::vector<double>& b)
        : _size{static_cast<int>(b.size())},
          _aux{}
{
    _aux.reserve(b.size());
    for (auto v : _aux) {
        v.reserve((b.size() * 2) + 1);
    }
    for (int i{0}; i < _size; ++i) {
        for (int j{0}; j < _size; ++j) {
            _aux[i][j] = a[i][j];
        }
    }
    for (int i{0}; i < _size; ++i) {
        _aux[i][_size + i] = 1.0;
    }

    for (int i{0}; i < _size; ++i) {
        _aux[i][_size + _size] = b[i];
    }

    _solve();

    utility::alg_assert(_certify_solution(a, b), "Gauss_jordan_elimination solution certification failed after construction");
}

std::vector<double> Gauss_jordan_elimination::primal()
{
    std::vector<double> x;
    x.reserve(static_cast<std::vector<double>::size_type>(_size));
    for (int i{0}; i < _size; ++i) {
        if (std::abs(_aux[i][i]) > _epsilon) {
            x[i] = _aux[i][_size + _size] / _aux[i][i];
        } else if (std::abs(_aux[i][_size + _size]) > _epsilon) {
            return {};
        }
    }
    return x;
}

std::vector<double> Gauss_jordan_elimination::dual()
{
    std::vector<double> y;
    y.reserve(static_cast<std::vector<double>::size_type>(_size));
    for (int i{0}; i < _size; ++i) {
        if ((std::abs(_aux[i][i]) <= _epsilon) && (std::abs(_aux[i][_size + _size]) > _epsilon)) {
            for (int j{0}; j < _size; ++j) {
                y[j] = _aux[i][_size + j];
            }
            return y;
        }
    }
    return {};
}

bool Gauss_jordan_elimination::is_feasible()
{
    return !primal().empty();
}

void Gauss_jordan_elimination::_solve()
{
    for (int p{0}; p < _size; ++p) {
        // show();

        int max{p};
        for (int i{p + 1}; i < _size; ++i) {
            if (std::abs(_aux[i][p]) > std::abs(_aux[max][p])) {
                max = i;
            }
        }

        _swap(p, max);

        if (std::abs(_aux[p][p]) <= _epsilon) {
            continue;
            // throw utility::Arithmetic_exception{"Matrix is singular or nearly singular"};
        }

        // pivot
        _pivot(p, p);
    }
    // show();
}

void Gauss_jordan_elimination::_swap(int row1, int row2)
{
    std::vector<double> temp = _aux[row1];
    _aux[row1] = _aux[row2];
    _aux[row2] = temp;
}

void Gauss_jordan_elimination::_pivot(int p, int q)
{
    for (int i{0}; i < _size; ++i) {
        double alpha = _aux[i][q] / _aux[p][q];
        for (int j{0}; j <= _size + _size; ++j) {
            if (i != p && j != q) { _aux[i][j] -= alpha * _aux[p][j]; }
        }
    }

    for (int i{0}; i < _size; ++i) {
        if (i != p) { _aux[i][q] = 0.0; }
    }

    for (int j{0}; j <= _size + _size; ++j) {
        if (j != q) { _aux[p][j] /= _aux[p][q]; }
    }
    _aux[p][q] = 1.0;
}

void Gauss_jordan_elimination::_show()
{
    for (int i{0}; i < _size; ++i) {
        for (int j{0}; j < _size; ++j) {
            Std_out::printf("%8.3f ", _aux[i][j]);
        }
        Std_out::printf("| ");
        for (int j{_size}; j < _size + _size; ++j) {
            Std_out::printf("%8.3f ", _aux[i][j]);
        }
        Std_out::printf("| %8.3f\n", _aux[i][_size + _size]);
    }
    Std_out::print_line();
}

bool Gauss_jordan_elimination::_certify_solution(std::vector<std::vector<double>>& a, std::vector<double>& b)
{
    if (is_feasible()) {
        std::vector<double> x = primal();
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                sum += a[i][j] * x[j];
            }
            if (std::abs(sum - b[i]) > _epsilon) {
                Std_out::print_line("not feasible");
                Std_out::printf("b[%d] = %8.3f, sum = %8.3f\n", i, b[i], sum);
                return false;
            }
        }
        return true;
    } else {
        std::vector<double> y{dual()};
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int i = 0; i < n; i++) {
                sum += a[i][j] * y[i];
            }
            if (std::abs(sum) > _epsilon) {
                Std_out::print_line("invalid certificate of infeasibility");
                Std_out::printf("sum = %8.3f\n", sum);
                return false;
            }
        }
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            sum += y[i] * b[i];
        }
        if (std::abs(sum) < _epsilon) {
            Std_out::print_line("invalid certificate of infeasibility");
            Std_out::printf("yb  = %8.3f\n", sum);
            return false;
        }
        return true;
    }
}

void Gje_tests::test(std::string&& name, std::vector<std::vector<double>>& a, std::vector<double>& b)
{
    Std_out::print_line("----------------------------------------------------");
    Std_out::print_line(name);
    Std_out::print_line("----------------------------------------------------");
    Gauss_jordan_elimination gaussian{a, b};
    if (gaussian.is_feasible()) {
        Std_out::print_line("Solution to Ax = b");
        std::vector<double> x = gaussian.primal();
        for (int i{0}; i < x.size(); ++i) {
            Std_out::printf("%10.6f\n", x[i]);
        }
    } else {
        Std_out::print_line("Certificate of infeasibility");
        std::vector<double> y = gaussian.dual();
        for (int j{0}; j < y.size(); ++j) {
            Std_out::printf("%10.6f\n", y[j]);
        }
    }
    Std_out::print_line();
    Std_out::print_line();
}

void Gje_tests::test1()
{
    std::vector<std::vector<double>> A = {
            {0, 1, 1},
            {2, 4, -2},
            {0, 3, 15}
    };
    std::vector<double> b = {4, 2, 36};
    Gje_tests::test("test 1", A, b);
}

void Gje_tests::test2()
{
    std::vector<std::vector<double>> A = {
            {1,  -3, 1},
            {2,  -8, 8},
            {-6, 3,  -15}
    };
    std::vector<double> b = {4, -2, 9};
    Gje_tests::test("test 2", A, b);
}

void Gje_tests::test3()
{
    std::vector<std::vector<double>> A = {
            {2,  -3, -1, 2, 3},
            {4,  -4, -1, 4, 11},
            {2,  -5, -2, 2, -1},
            {0,  2,  1,  0, 4},
            {-4, 6,  0,  0, 7},
    };
    std::vector<double> b = {4, 4, 9, -6, 5};
    Gje_tests::test("test 3", A, b);
}

void Gje_tests::test4()
{
    std::vector<std::vector<double>> A = {
            {2,  -3, -1, 2, 3},
            {4,  -4, -1, 4, 11},
            {2,  -5, -2, 2, -1},
            {0,  2,  1,  0, 4},
            {-4, 6,  0,  0, 7},
    };
    std::vector<double> b = {4, 4, 9, -5, 5};
    Gje_tests::test("test 4", A, b);
}

void Gje_tests::test5()
{
    std::vector<std::vector<double>> A = {
            {2,  -1, 1},
            {3,  2,  -4},
            {-6, 3,  -3},
    };
    std::vector<double> b = {1, 4, 2};
    Gje_tests::test("test 5", A, b);
}

void Gje_tests::test6()
{
    std::vector<std::vector<double>> A = {
            {1,  -1, 2},
            {4,  4,  -2},
            {-2, 2,  -4},
    };
    std::vector<double> b = {-3, 1, 6};
    Gje_tests::test("test 6 (infinitely many solutions)", A, b);
}
