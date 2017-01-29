#include "Gaussian_elimination.h"
#include "Std_out.h"
#include "utility.h"

Gaussian_elimination::Gaussian_elimination(std::vector<std::vector<double>>& a, std::vector<double>& b)
        : _m{static_cast<int>(a.size())},
          _n{static_cast<int>(a.size())},
          _a{}
{

    if (b.size() != _m) { throw utility::Illegal_argument_exception{"Dimensions disagree"}; }

    _a.reserve(a.size());
    for (auto v : _a) {
        v.reserve(a.size() + 1);
    }
    for (int i{0}; i < _m; ++i) {
        for (int j{0}; j < _n; ++j) {
            _a[i][j] = a[i][j];
        }
    }
    for (int i{0}; i < _m; ++i) {
        _a[i][_n] = b[i];
    }

    _forward_elimination();

    utility::alg_assert(_certify_solution(a, b), "Gaussian_elimination solution certification check failed after construction");
}

std::vector<double> Gaussian_elimination::primal()
{
    std::vector<double> x;
    x.reserve(static_cast<std::vector<double>::size_type>(_n));
    for (int i{std::min(_n - 1, _m - 1)}; i >= 0; i--) {
        double sum = 0.0;
        for (int j{i + 1}; j < _n; ++j) {
            sum += _a[i][j] * x[j];
        }

        if (std::abs(_a[i][i]) > _epsilon) {
            x[i] = (_a[i][_n] - sum) / _a[i][i];
        } else if (std::abs(_a[i][_n] - sum) > _epsilon) {
            return {};
        }
    }

    for (int i{_n}; i < _m; ++i) {
        double sum = 0.0;
        for (int j{0}; j < _n; ++j) {
            sum += _a[i][j] * x[j];
        }
        if (std::abs(_a[i][_n] - sum) > _epsilon) {
            return {};
        }
    }
    return x;
}

bool Gaussian_elimination::is_feasible()
{
    return !primal().empty();
}

void Gaussian_elimination::_forward_elimination()
{
    for (int p{0}; p < std::min(_m, _n); ++p) {

        int max{p};
        for (int i{p + 1}; i < _m; ++i) {
            if (std::abs(_a[i][p]) > std::abs(_a[max][p])) {
                max = i;
            }
        }

        _swap(p, max);

        if (std::abs(_a[p][p]) <= _epsilon) {
            continue;
        }

        _pivot(p);
    }
}

void Gaussian_elimination::_swap(int row1, int row2)
{
    std::vector<double> temp = _a[row1];
    _a[row1] = _a[row2];
    _a[row2] = temp;
}

void Gaussian_elimination::_pivot(int p)
{
    for (int i{p + 1}; i < _m; ++i) {
        double alpha = _a[i][p] / _a[p][p];
        for (int j{p}; j <= _n; ++j) {
            _a[i][j] -= alpha * _a[p][j];
        }
    }
}

bool Gaussian_elimination::_certify_solution(std::vector<std::vector<double>>& A, std::vector<double>& b)
{
    if (!is_feasible()) { return true; }
    std::vector<double> x = primal();
    for (int i{0}; i < _m; ++i) {
        double sum = 0.0;
        for (int j{0}; j < _n; ++j) {
            sum += A[i][j] * x[j];
        }
        if (std::abs(sum - b[i]) > _epsilon) {
            Std_out::print_line("not feasible");
            std::string s{"b[" + std::to_string(i) + "] = " + std::to_string(b[i]) + ", sum = " + std::to_string(sum)};
            Std_out::print_line(s);
            return false;
        }
    }
    return true;
}

void Ge_tests::test(std::string&& name, std::vector<std::vector<double>>& A, std::vector<double>& b)
{
    Std_out::print_line("----------------------------------------------------");
    Std_out::print_line(name);
    Std_out::print_line("----------------------------------------------------");
    Gaussian_elimination gaussian{A, b};
    std::vector<double> x{gaussian.primal()};
    if (gaussian.is_feasible()) {
        for (int i{0}; i < x.size(); ++i) {
            Std_out::printf("%.6f\n", x[i]);
        }
    } else {
        Std_out::print_line("System is infeasible");
    }
    Std_out::print_line();
    Std_out::print_line();
}

void Ge_tests::test1()
{
    std::vector<std::vector<double>> A = {
            {0, 1, 1},
            {2, 4, -2},
            {0, 3, 15}
    };
    std::vector<double> b = {4, 2, 36};
    Ge_tests::test("test 1 (3-by-3 system, nonsingular)", A, b);
}

void Ge_tests::test2()
{
    std::vector<std::vector<double>> A = {
            {1,  -3, 1},
            {2,  -8, 8},
            {-6, 3,  -15}
    };
    std::vector<double> b = {4, -2, 9};
    Ge_tests::test("test 2 (3-by-3 system, nonsingular)", A, b);
}

void Ge_tests::test3()
{
    std::vector<std::vector<double>> A = {
            {2,  -3, -1, 2, 3},
            {4,  -4, -1, 4, 11},
            {2,  -5, -2, 2, -1},
            {0,  2,  1,  0, 4},
            {-4, 6,  0,  0, 7},
    };
    std::vector<double> b = {4, 4, 9, -6, 5};
    Ge_tests::test("test 3 (5-by-5 system, no solutions)", A, b);
}

void Ge_tests::test4()
{
    std::vector<std::vector<double>> A = {
            {2,  -3, -1, 2, 3},
            {4,  -4, -1, 4, 11},
            {2,  -5, -2, 2, -1},
            {0,  2,  1,  0, 4},
            {-4, 6,  0,  0, 7},
    };
    std::vector<double> b = {4, 4, 9, -5, 5};
    Ge_tests::test("test 4 (5-by-5 system, infinitely many solutions)", A, b);
}

void Ge_tests::test5()
{
    std::vector<std::vector<double>> A = {
            {2,  -1, 1},
            {3,  2,  -4},
            {-6, 3,  -3},
    };
    std::vector<double> b = {1, 4, 2};
    Ge_tests::test("test 5 (3-by-3 system, no solutions)", A, b);
}

void Ge_tests::test6()
{
    std::vector<std::vector<double>> A = {
            {1,  -1, 2},
            {4,  4,  -2},
            {-2, 2,  -4},
    };
    std::vector<double> b = {-3, 1, 6};
    Ge_tests::test("test 6 (3-by-3 system, infinitely many solutions)", A, b);
}

void Ge_tests::test7()
{
    std::vector<std::vector<double>> A = {
            {0, 1, 1},
            {2, 4, -2},
            {0, 3, 15},
            {2, 8, 14}
    };
    std::vector<double> b = {4, 2, 36, 42};
    Ge_tests::test("test 7 (4-by-3 system, full rank)", A, b);
}

void Ge_tests::test8()
{
    std::vector<std::vector<double>> A = {
            {0, 1, 1},
            {2, 4, -2},
            {0, 3, 15},
            {2, 8, 14}
    };
    std::vector<double> b = {4, 2, 36, 40};
    Ge_tests::test("test 8 (4-by-3 system, no solution)", A, b);
}

void Ge_tests::test9()
{
    std::vector<std::vector<double>> A = {
            {1,  -3, 1,   1},
            {2,  -8, 8,   2},
            {-6, 3,  -15, 3}
    };
    std::vector<double> b = {4, -2, 9};
    Ge_tests::test("test 9 (3-by-4 system, full rank)", A, b);
}
