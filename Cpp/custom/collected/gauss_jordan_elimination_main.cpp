#include "Std_random.h"
#include "Gauss_jordan_elimination.h"

int main(int argc, char* argv[])
{
    Gauss_jordan_elimination::test1();
    Gauss_jordan_elimination::test2();
    Gauss_jordan_elimination::test3();
    Gauss_jordan_elimination::test4();
    Gauss_jordan_elimination::test5();
    Gauss_jordan_elimination::test6();

    int n{utility::str_to_num(argv[1])};
    std::vector<std::vector<double>> a;
    a.reserve(n);
    for (int i = 0; i < n; ++i) {
        a[i] = std::vector<double>{};
        a[i].reserve(n);
        for (int j = 0; j < n; ++j) {
            a[i][j] = Std_random::uniform(1000);
        }
    }
    std::vector<double> b;
    b.reserve(n);
    for (int i = 0; i < n; ++i) {
        b[i] = Std_random::uniform(1000);
    }
    Gauss_jordan_elimination::test("random " + n + "-by-" + n + " (likely full rank)", a, b);

    a.clear();
    a.reserve(n);
    for (int i = 0; i < n - 1; ++i) {
        a[i] = std::vector<double>{};
        a[i].reserve(n);
        for (int j = 0; j < n; ++j) {
            a[i][j] = Std_random::uniform(1000);
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        double alpha = Std_random::uniform(11) - 5.0;
        for (int j = 0; j < n; ++j) {
            a[n - 1][j] += alpha * a[i][j];
        }
    }
    b = new double[n];
    for (int i = 0; i < n; ++i) {
        b[i] = Std_random::uniform(1000);
    }
    Gauss_jordan_elimination::test("random " + n + "-by-" + n + " (likely infeasible)", a, b);
    return 0;
}