#include "Gauss_jordan_elimination.h"

Gauss_jordan_elimination::Gauss_jordan_elimination(std::vector<std::vector<double>>& A, std::vector<double>& b)
{
    n = b.length;

    // build augmented matrix
    a = new double[n][n + n + 1];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            a[i][j] = A[i][j];

    // only needed if you want to find certificate of infeasibility (or compute inverse)
    for (int i = 0; i < n; ++i)
        a[i][n + i] = 1.0;

    for (int i = 0; i < n; ++i)
        a[i][n + n] = b[i];

    solve();

    assert certifySolution(A, b);
}

std::vector<double> Gauss_jordan_elimination::primal()
{
    std::vector<double> x = new double[n];
    for (int i = 0; i < n; ++i) {
        if (std::abs(a[i][i]) > EPSILON)
            x[i] = a[i][n + n] / a[i][i];
        else if (std::abs(a[i][n + n]) > EPSILON)
            return null;
    }
    return x;
}

std::vector<double> Gauss_jordan_elimination::dual()
{
    std::vector<double> y = new double[n];
    for (int i = 0; i < n; ++i) {
        if ((std::abs(a[i][i]) <= EPSILON) && (std::abs(a[i][n + n]) > EPSILON)) {
            for (int j = 0; j < n; ++j)
                y[j] = a[i][n + j];
            return y;
        }
    }
    return null;
}

bool Gauss_jordan_elimination::isFeasible()
{
    if (isFeasible()) {
        std::vector<double> x = primal();
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                sum += A[i][j] * x[j];
            }
            if (std::abs(sum - b[i]) > EPSILON) {
                Std_out::print_line("not feasible");
                Std_out::printf("b[%d] = %8.3f, sum = %8.3f\n", i, b[i], sum);
                return false;
            }
        }
        return true;
    }

        // or that yA = 0, yb != 0
    else {
        std::vector<double> y = dual();
        for (int j = 0; j < n; ++j) {
            double sum = 0.0;
            for (int i = 0; i < n; ++i) {
                sum += A[i][j] * y[i];
            }
            if (std::abs(sum) > EPSILON) {
                Std_out::print_line("invalid certificate of infeasibility");
                Std_out::printf("sum = %8.3f\n", sum);
                return false;
            }
        }
        double sum = 0.0;
        for (int i = 0; i < n; ++i) {
            sum += y[i] * b[i];
        }
        if (std::abs(sum) < EPSILON) {
            Std_out::print_line("invalid certificate of infeasibility");
            Std_out::printf("yb  = %8.3f\n", sum);
            return false;
        }
        return true;
    }
}

void Gauss_jordan_elimination::solve()
{
    for (int p = 0; p < n; ++p) {
        // show();

        // find pivot row using partial pivoting
        int max = p;
        for (int i = p + 1; i < n; ++i) {
            if (std::abs(a[i][p]) > std::abs(a[max][p])) {
                max = i;
            }
        }

        // exchange row p with row max
        swap(p, max);

        // singular or nearly singular
        if (std::abs(a[p][p]) <= EPSILON) {
            continue;
            // throw new ArithmeticException("Matrix is singular or nearly singular");
        }

        // pivot
        pivot(p, p);
    }
    // show();
}

void Gauss_jordan_elimination::swap(int row1, int row2)
{
    std::vector<double> temp = a[row1];
    a[row1] = a[row2];
    a[row2] = temp;
}

void Gauss_jordan_elimination::pivot(int p, int q)
{
    for (int i = 0; i < n; ++i) {
        double alpha = a[i][q] / a[p][q];
        for (int j = 0; j <= n + n; ++j) {
            if (i != p && j != q) a[i][j] -= alpha * a[p][j];
        }
    }

    // zero out column q
    for (int i = 0; i < n; ++i)
        if (i != p) a[i][q] = 0.0;

    // scale row p (ok to go from q+1 to n, but do this for consistency with simplex pivot)
    for (int j = 0; j <= n + n; ++j)
        if (j != q) a[p][j] /= a[p][q];
    a[p][q] = 1.0;
}

void Gauss_jordan_elimination::show()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Std_out::printf("%8.3f ", a[i][j]);
        }
        Std_out::printf("| ");
        for (int j = n; j < n + n; ++j) {
            Std_out::printf("%8.3f ", a[i][j]);
        }
        Std_out::printf("| %8.3f\n", a[i][n + n]);
    }
    Std_out::print_line();
}

bool Gauss_jordan_elimination::certifySolution(std::vector<std::vector<double>>& A, std::vector<double>& b)
{
    return false;
}

void Gauss_jordan_elimination::test(std::string& name, std::vector<std::vector<double>>& A, std::vector<double>& b)
{
    Std_out::print_line("----------------------------------------------------");
    Std_out::print_line(name);
    Std_out::print_line("----------------------------------------------------");
    GaussJordanElimination gaussian = new GaussJordanElimination(A, b);
    if (gaussian.isFeasible()) {
        Std_out::print_line("Solution to Ax = b");
        std::vector<double> x = gaussian.primal();
        for (int i = 0; i < x.length; ++i) {
            Std_out::printf("%10.6f\n", x[i]);
        }
    } else {
        Std_out::print_line("Certificate of infeasibility");
        std::vector<double> y = gaussian.dual();
        for (int j = 0; j < y.length; ++j) {
            Std_out::printf("%10.6f\n", y[j]);
        }
    }
    Std_out::print_line();
    Std_out::print_line();
}

void Gauss_jordan_elimination::test1()
{
    std::vector<std::vector<double>> A = {
            {0, 1, 1},
            {2, 4, -2},
            {0, 3, 15}
    };
    std::vector<double> b = {4, 2, 36};
    test("test 1", A, b);
}

void Gauss_jordan_elimination::test2()
{
    std::vector<std::vector<double>> A = {
            {1, -3, 1},
            {2, -8, 8},
            {-6, 3, -15}
    };
    std::vector<double> b = {4, -2, 9};
    test("test 2", A, b);
}

void Gauss_jordan_elimination::test3()
{
    std::vector<std::vector<double>> A = {
            {2, -3, -1, 2, 3},
            {4, -4, -1, 4, 11},
            {2, -5, -2, 2, -1},
            {0, 2, 1, 0, 4},
            {-4, 6, 0, 0, 7},
    };
    std::vector<double> b = {4, 4, 9, -6, 5};
    test("test 3", A, b);
}

void Gauss_jordan_elimination::test4()
{
    std::vector<std::vector<double>> A = {
            {2, -3, -1, 2, 3},
            {4, -4, -1, 4, 11},
            {2, -5, -2, 2, -1},
            {0, 2, 1, 0, 4},
            {-4, 6, 0, 0, 7},
    };
    std::vector<double> b = {4, 4, 9, -5, 5};
    test("test 4", A, b);
}

void Gauss_jordan_elimination::test5()
{
    std::vector<std::vector<double>> A = {
            {2, -1, 1},
            {3, 2, -4},
            {-6, 3, -3},
    };
    std::vector<double> b = {1, 4, 2};
    test("test 5", A, b);
}

void Gauss_jordan_elimination::test6()
{
    std::vector<std::vector<double>> A = {
            {1, -1, 2},
            {4, 4, -2},
            {-2, 2, -4},
    };
    std::vector<double> b = {-3, 1, 6};
    test("test 6 (infinitely many solutions)", A, b);
}
