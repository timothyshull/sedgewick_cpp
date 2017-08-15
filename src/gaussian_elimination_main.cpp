#include "Gaussian_elimination.h"
#include "Std_random.h"

int main(int argc, char* argv[])
{
    Ge_tests::test1();
    Ge_tests::test2();
    Ge_tests::test3();
    Ge_tests::test4();
    Ge_tests::test5();
    Ge_tests::test6();
    Ge_tests::test7();
    Ge_tests::test8();
    Ge_tests::test9();

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

    Ge_tests::test(std::string{std::to_string(n) + "-by-" + std::to_string(n) + " (probably nonsingular)"}, a, b);
    return 0;
}