#include "Linear_programming.h"

Linear_programming::Linear_programming(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& c)
{
    m = b.length;
    n = c.length;
    for (int i = 0; i < m; i++)
        if (!(b[i] >= 0)) throw new IllegalArgumentException("RHS must be nonnegative");

    a = new double[m + 1][n + m + 1];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = A[i][j];
    for (int i = 0; i < m; i++)
        a[i][n + i] = 1.0;
    for (int j = 0; j < n; j++)
        a[m][j] = c[j];
    for (int i = 0; i < m; i++)
        a[i][m + n] = b[i];

    basis = new int[m];
    for (int i = 0; i < m; i++)
        basis[i] = n + i;

    solve();

    // check optimality conditions
    assert check(A, b, c);
}

void Linear_programming::solve()
{
    while (true) {

        // find entering column q
        int q = bland();
        if (q == -1) break;  // optimal

        // find leaving row p
        int p = minRatioRule(q);
        if (p == -1) throw new ArithmeticException("Linear program is unbounded");

        // pivot
        pivot(p, q);

        // update basis
        basis[p] = q;
    }
}

int Linear_programming::bland()
{
    for (int j = 0; j < m + n; j++)
        if (a[m][j] > 0) return j;
    return -1;  // optimal
}

int Linear_programming::dantzig()
{
    int q = 0;
    for (int j = 1; j < m + n; j++)
        if (a[m][j] > a[m][q]) q = j;

    if (a[m][q] <= 0) return -1;  // optimal
    else return q;
}

int Linear_programming::minRatioRule(int q)
{
    int p = -1;
    for (int i = 0; i < m; i++) {
        // if (a[i][q] <= 0) continue;
        if (a[i][q] <= EPSILON) continue;
        else if (p == -1) p = i;
        else if ((a[i][m + n] / a[i][q]) < (a[p][m + n] / a[p][q])) p = i;
    }
    return p;
}

void Linear_programming::pivot(int p, int q)
{
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= m + n; j++)
            if (i != p && j != q) a[i][j] -= a[p][j] * a[i][q] / a[p][q];

    // zero out column q
    for (int i = 0; i <= m; i++)
        if (i != p) a[i][q] = 0.0;

    // scale row p
    for (int j = 0; j <= m + n; j++)
        if (j != q) a[p][j] /= a[p][q];
    a[p][q] = 1.0;
}

double Linear_programming::value()
{
    return -a[m][m + n];
}

std::vector<double> Linear_programming::primal()
{
    double[] x = new double[n];
    for (int i = 0; i < m; i++)
        if (basis[i] < n) x[basis[i]] = a[i][m + n];
    return x;
}

std::vector<double> Linear_programming::dual()
{
    double[] y = new double[m];
    for (int i = 0; i < m; i++)
        y[i] = -a[m][n + i];
    return y;
}

bool Linear_programming::isPrimalFeasible(std::vector<std::vector<double>>& A, std::vector<double>& b)
{
    double[] x = primal();

    // check that x >= 0
    for (int j = 0; j < x.length; j++) {
        if (x[j] < 0.0) {
            StdOut.println("x[" + j + "] = " + x[j] + " is negative");
            return false;
        }
    }

    // check that Ax <= b
    for (int i = 0; i < m; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        if (sum > b[i] + EPSILON) {
            StdOut.println("not primal feasible");
            StdOut.println("b[" + i + "] = " + b[i] + ", sum = " + sum);
            return false;
        }
    }
    return true;
}

bool Linear_programming::isDualFeasible(std::vector<std::vector<double>>& A, std::vector<double>& c)
{
    double[] y = dual();

    // check that y >= 0
    for (int i = 0; i < y.length; i++) {
        if (y[i] < 0.0) {
            StdOut.println("y[" + i + "] = " + y[i] + " is negative");
            return false;
        }
    }

    // check that yA >= c
    for (int j = 0; j < n; j++) {
        double sum = 0.0;
        for (int i = 0; i < m; i++) {
            sum += A[i][j] * y[i];
        }
        if (sum < c[j] - EPSILON) {
            StdOut.println("not dual feasible");
            StdOut.println("c[" + j + "] = " + c[j] + ", sum = " + sum);
            return false;
        }
    }
    return true;
}

bool Linear_programming::isOptimal(std::vector<double>& b, std::vector<double>& c)
{
    double[] x = primal();
    double[] y = dual();
    double value = value();

    // check that value = cx = yb
    double value1 = 0.0;
    for (int j = 0; j < x.length; j++)
        value1 += c[j] * x[j];
    double value2 = 0.0;
    for (int i = 0; i < y.length; i++)
        value2 += y[i] * b[i];
    if (Math.abs(value - value1) > EPSILON || Math.abs(value - value2) > EPSILON) {
        StdOut.println("value = " + value + ", cx = " + value1 + ", yb = " + value2);
        return false;
    }

    return true;
}

bool Linear_programming::check(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& c)
{
    return isPrimalFeasible(A, b) && isDualFeasible(A, c) && isOptimal(b, c);
}

void Linear_programming::show()
{
    StdOut.println("m = " + m);
    StdOut.println("n = " + n);
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m + n; j++) {
            StdOut.printf("%7.2f ", a[i][j]);
            // StdOut.printf("%10.7f ", a[i][j]);
        }
        StdOut.println();
    }
    StdOut.println("value = " + value());
    for (int i = 0; i < m; i++)
        if (basis[i] < n) StdOut.println("x_" + basis[i] + " = " + a[i][m + n]);
    StdOut.println();
}

void Linear_programming::test(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& c)
{
    LinearProgramming lp = new LinearProgramming(A, b, c);
    StdOut.println("value = " + lp.value());
    double[] x = lp.primal();
    for (int i = 0; i < x.length; i++)
        StdOut.println("x[" + i + "] = " + x[i]);
    double[] y = lp.dual();
    for (int j = 0; j < y.length; j++)
        StdOut.println("y[" + j + "] = " + y[j]);
}

void Linear_programming::test1()
{
    double[][] A = {
            {-1, 1, 0},
            {1, 4, 0},
            {2, 1, 0},
            {3, -4, 0},
            {0, 0, 1},
    };
    double[] c = {1, 1, 1};
    double[] b = {5, 45, 27, 24, 4};
    test(A, b, c);
}

void Linear_programming::test2()
{
    double[] c = {13.0, 23.0};
    double[] b = {480.0, 160.0, 1190.0};
    double[][] A = {
            {5.0, 15.0},
            {4.0, 4.0},
            {35.0, 20.0},
    };
    test(A, b, c);
}

void Linear_programming::test3()
{
    double[] c = {2.0, 3.0, -1.0, -12.0};
    double[] b = {3.0, 2.0};
    double[][] A = {
            {-2.0, -9.0, 1.0, 9.0},
            {1.0, 1.0, -1.0, -2.0},
    };
    test(A, b, c);
}

void Linear_programming::test4()
{
    double[] c = {10.0, -57.0, -9.0, -24.0};
    double[] b = {0.0, 0.0, 1.0};
    double[][] A = {
            {0.5, -5.5, -2.5, 9.0},
            {0.5, -1.5, -0.5, 1.0},
            {1.0, 0.0, 0.0, 0.0},
    };
    test(A, b, c);
}
