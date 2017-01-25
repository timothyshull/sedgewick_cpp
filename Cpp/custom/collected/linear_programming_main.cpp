#include "Std_random.h"
#include "Std_out.h"
#include "Linear_programming.h"

int main(int argc, char* argv[])
{
    Std_out::print_line("----- test 1 --------------------");
    Linear_programming::test1();
    Std_out::print_line("----- test 2 --------------------");
    Linear_programming::test2();
    Std_out::print_line("----- test 3 --------------------");
    try {
        Linear_programming::test3();
    } catch (ArithmeticException e) {
        e.printStackTrace();
    }

    Std_out::print_line("----- test 4 --------------------");
    Linear_programming::test4();

    Std_out::print_line("----- test random ---------------");
    int m = utility::str_to_num(argv[1]);
    int n = utility::str_to_num(argv[2]);
    std::vector<double> c;
    c.reserve(n);
    std::vector<double> b;
    b.reserve(m);
    std::vector<std::vector<double>> A;
    A.reserve(m);
    for (int i{0}; i < m; ++i) {
        A[i] = std::vector<double>{};
        A[i].reserve(n);
    }
    for (int j{0}; j < n; ++j) {
        c[j] = Std_random::uniform(1000);
    }
    for (int i{0}; i < m; ++i) {
        b[i] = Std_random::uniform(1000);
    }
    for (int i{0}; i < m; ++i) {
        for (int j{0}; j < n; ++j) {
            A[i][j] = Std_random::uniform(100);
        }
    }
    Linear_programming lp{A, b, c};
    Std_out::print_line(lp.value());
    return 0;
}