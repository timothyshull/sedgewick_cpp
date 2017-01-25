#include "Gaussian_elimination.h"
#include "Std_random.h"

int main(int argc, char* argv[])
{
    Gaussian_elimination::test1();
    Gaussian_elimination::test2();
    Gaussian_elimination::test3();
    Gaussian_elimination::test4();
    Gaussian_elimination::test5();
    Gaussian_elimination::test6();
    Gaussian_elimination::test7();
    Gaussian_elimination::test8();
    Gaussian_elimination::test9();

    int n{utility::str_to_num(argv[1])};
    std::vector<std::vector<double>> A;
    A.reserve(n);
    for (int i = 0; i < n; ++i) {
        A[i] = std::vector<double>{};
        A[i].reserve(n);
        for (int j = 0; j < n; ++j) {
            A[i][j] = Std_random::uniform(1000);
        }
    }
    std::vector<double> b;
    b.reserve(n);
    for (int i = 0; i < n; ++i) {
        b[i] = Std_random::uniform(1000);
    }

    Gaussian_elimination::test(n + "-by-" + n + " (probably nonsingular)", A, b);
    return 0;
}