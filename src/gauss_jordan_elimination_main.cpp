#include "Std_random.h"
#include "Gauss_jordan_elimination.h"

int main(int argc, char* argv[])
{
    Gje_tests::test1();
    Gje_tests::test2();
    Gje_tests::test3();
    Gje_tests::test4();
    Gje_tests::test5();
    Gje_tests::test6();

    auto n = utility::str_to_num(argv[1]);
    std::vector<std::vector<double>> a;
    a.reserve(static_cast<std::vector<double>::size_type>(n));
    for (auto i = 0; i < n; ++i) {
        a[i] = std::vector<double>{};
        a[i].reserve(static_cast<std::vector<double>::size_type>(n));
        for (auto j = 0; j < n; ++j) {
            a[i][j] = Std_random::uniform(1000);
        }
    }
    std::vector<double> b;
    b.reserve(static_cast<std::vector<double>::size_type>(n));
    for (auto i = 0; i < n; ++i) {
        b[i] = Std_random::uniform(1000);
    }
    Gje_tests::test("random " + std::to_string(n) + "-by-" + std::to_string(n) + " (likely full rank)", a, b);

    a.clear();
    a.reserve(static_cast<std::vector<double>::size_type>(n));
    for (auto i = 0; i < n - 1; ++i) {
        a[i] = std::vector<double>{};
        a[i].reserve(static_cast<std::vector<double>::size_type>(n));
        for (auto j = 0; j < n; ++j) {
            a[i][j] = Std_random::uniform(1000);
        }
    }
    for (auto i = 0; i < n - 1; ++i) {
        double alpha = Std_random::uniform(11) - 5.0;
        for (auto j = 0; j < n; ++j) {
            a[n - 1][j] += alpha * a[i][j];
        }
    }
    b = std::vector<double>(static_cast<std::vector<double>::size_type>(n));
    for (auto i = 0; i < n; ++i) {
        b[i] = Std_random::uniform(1000);
    }
    Gje_tests::test("random " + std::to_string(n) + "-by-" + std::to_string(n) + " (likely infeasible)", a, b);
    return 0;
}