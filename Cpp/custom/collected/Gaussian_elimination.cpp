#include "Gaussian_elimination.h"

Gaussian_elimination::Gaussian_elimination(std::vector<std::vector<double>>& A, std::vector<double>& b)
{
    m = A.length;
    n = A[0].length;

    if (b.length != m) throw new IllegalArgumentException("Dimensions disagree");

    // build augmented matrix
    a = new double[m][n + 1];
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            a[i][j] = A[i][j];
    for (int i = 0; i < m; ++i)
        a[i][n] = b[i];

    forwardElimination();

    assert certifySolution(A, b);
}

std::vector<double> Gaussian_elimination::primal()
{
    std::vector<double> x = new double[n];
    for (int i = Math.min(n - 1, m - 1); i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += a[i][j] * x[j];
        }

        if (Math.abs(a[i][i]) > EPSILON)
            x[i] = (a[i][n] - sum) / a[i][i];
        else if (Math.abs(a[i][n] - sum) > EPSILON)
            return null;
    }

    // redundant rows
    for (int i = n; i < m; ++i) {
        double sum = 0.0;
        for (int j = 0; j < n; ++j) {
            sum += a[i][j] * x[j];
        }
        if (Math.abs(a[i][n] - sum) > EPSILON)
            return null;
    }
    return x;
}

bool Gaussian_elimination::isFeasible()
{
    return primal() != null;
}

void Gaussian_elimination::forwardElimination()
{
    for (int p = 0; p < Math.min(m, n); ++p) {

        // find pivot row using partial pivoting
        int max = p;
        for (int i = p + 1; i < m; ++i) {
            if (Math.abs(a[i][p]) > Math.abs(a[max][p])) {
                max = i;
            }
        }

        // swap
        swap(p, max);

        // singular or nearly singular
        if (Math.abs(a[p][p]) <= EPSILON) {
            continue;
        }

        // pivot
        pivot(p);
    }
}

void Gaussian_elimination::swap(int row1, int row2)
{
    std::vector<double> temp = a[row1];
    a[row1] = a[row2];
    a[row2] = temp;
}

void Gaussian_elimination::pivot(int p, int q)
{
    for (int i = p + 1; i < m; ++i) {
        double alpha = a[i][p] / a[p][p];
        for (int j = p; j <= n; ++j) {
            a[i][j] -= alpha * a[p][j];
        }
    }
}

bool Gaussian_elimination::certifySolution(std::vector<std::vector<double>>& A, std::vector<double>& b)
{
    if (!isFeasible()) return true;
    std::vector<double> x = primal();
    for (int i = 0; i < m; ++i) {
        double sum = 0.0;
        for (int j = 0; j < n; ++j) {
            sum += A[i][j] * x[j];
        }
        if (Math.abs(sum - b[i]) > EPSILON) {
            Std_out::print_line("not feasible");
            Std_out::print_line("b[" + i + "] = " + b[i] + ", sum = " + sum);
            return false;
        }
    }
    return true;
}

void Gaussian_elimination::test(std::string& name, std::vector<std::vector<double>>& A, std::vector<double>& b)
{
    Std_out::print_line("----------------------------------------------------");
    Std_out::print_line(name);
    Std_out::print_line("----------------------------------------------------");
    GaussianElimination gaussian = new GaussianElimination(A, b);
    std::vector<double> x = gaussian.primal();
    if (gaussian.isFeasible()) {
        for (int i = 0; i < x.length; ++i) {
            Std_out::printf("%.6f\n", x[i]);
        }
    } else {
        Std_out::print_line("System is infeasible");
    }
    Std_out::print_line();
    Std_out::print_line();
}

void Gaussian_elimination::test1()
{
    std::vector<std::vector<double>> A = {
            {0, 1, 1},
            {2, 4, -2},
            {0, 3, 15}
    };
    std::vector<double> b = {4, 2, 36};
    test("test 1 (3-by-3 system, nonsingular)", A, b);
}

void Gaussian_elimination::test2()
{
    std::vector<std::vector<double>> A = {
            {1, -3, 1},
            {2, -8, 8},
            {-6, 3, -15}
    };
    std::vector<double> b = {4, -2, 9};
    test("test 2 (3-by-3 system, nonsingular)", A, b);
}

void Gaussian_elimination::test3()
{
    std::vector<std::vector<double>> A = {
            {2, -3, -1, 2, 3},
            {4, -4, -1, 4, 11},
            {2, -5, -2, 2, -1},
            {0, 2, 1, 0, 4},
            {-4, 6, 0, 0, 7},
    };
    std::vector<double> b = {4, 4, 9, -6, 5};
    test("test 3 (5-by-5 system, no solutions)", A, b);
}

void Gaussian_elimination::test4()
{
    std::vector<std::vector<double>> A = {
            {2, -3, -1, 2, 3},
            {4, -4, -1, 4, 11},
            {2, -5, -2, 2, -1},
            {0, 2, 1, 0, 4},
            {-4, 6, 0, 0, 7},
    };
    std::vector<double> b = {4, 4, 9, -5, 5};
    test("test 4 (5-by-5 system, infinitely many solutions)", A, b);
}

void Gaussian_elimination::test5()
{
    std::vector<std::vector<double>> A = {
            {2, -1, 1},
            {3, 2, -4},
            {-6, 3, -3},
    };
    std::vector<double> b = {1, 4, 2};
    test("test 5 (3-by-3 system, no solutions)", A, b);
}

void Gaussian_elimination::test6()
{
    std::vector<std::vector<double>> A = {
            {1, -1, 2},
            {4, 4, -2},
            {-2, 2, -4},
    };
    std::vector<double> b = {-3, 1, 6};
    test("test 6 (3-by-3 system, infinitely many solutions)", A, b);
}

void Gaussian_elimination::test7()
{
    std::vector<std::vector<double>> A = {
            {0, 1, 1},
            {2, 4, -2},
            {0, 3, 15},
            {2, 8, 14}
    };
    std::vector<double> b = {4, 2, 36, 42};
    test("test 7 (4-by-3 system, full rank)", A, b);
}

void Gaussian_elimination::test8()
{
    std::vector<std::vector<double>> A = {
            {0, 1, 1},
            {2, 4, -2},
            {0, 3, 15},
            {2, 8, 14}
    };
    std::vector<double> b = {4, 2, 36, 40};
    test("test 8 (4-by-3 system, no solution)", A, b);
}

void Gaussian_elimination::test9()
{
    std::vector<std::vector<double>> A = {
            {1, -3, 1, 1},
            {2, -8, 8, 2},
            {-6, 3, -15, 3}
    };
    std::vector<double> b = {4, -2, 9};
    test("test 9 (3-by-4 system, full rank)", A, b);
}
