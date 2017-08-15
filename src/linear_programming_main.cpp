#include "Std_random.h"
#include "Std_out.h"
#include "Linear_programming.h"

int main(int argc, char* argv[])
{
    Std_out::print_line("----- test 1 --------------------");
    Lp_tests::test1();
    Std_out::print_line("----- test 2 --------------------");
    Lp_tests::test2();
    Std_out::print_line("----- test 3 --------------------");
    try {
        Lp_tests::test3();
    } catch (utility::Arithmetic_exception& e) {
        Std_out::print_line(e.what());
    }

    Std_out::print_line("----- test 4 --------------------");
    Lp_tests::test4();

    Std_out::print_line("----- test random ---------------");
    auto m = utility::str_to_num(argv[1]);
    auto n = utility::str_to_num(argv[2]);
    std::vector<double> c;
    c.reserve(static_cast<std::vector<double>::size_type>(n));
    std::vector<double> b;
    b.reserve(static_cast<std::vector<double>::size_type>(m));
    std::vector<std::vector<double>> a;
    a.reserve(static_cast<std::vector<std::vector<double>>::size_type>(m));
    for (auto i = 0; i < m; ++i) {
        a[i] = std::vector<double>{};
        a[i].reserve(static_cast<std::vector<double>::size_type>(n));
    }
    for (auto j = 0; j < n; ++j) {
        c[j] = Std_random::uniform(1000);
    }
    for (auto i = 0; i < m; ++i) {
        b[i] = Std_random::uniform(1000);
    }
    for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j) {
            a[i][j] = Std_random::uniform(100);
        }
    }
    Linear_programming lp{a, b, c};
    Std_out::print_line(lp.value());
    return 0;
}