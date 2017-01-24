#include "utility.h"

int main(int argc, char *argv[]) {
    test1();
    test2();
    test3();
    test4();
    test5();

    int m = utility::safe_convert_integer(argv[1]);
    int n = utility::safe_convert_integer(argv[2]);
    std::vector<std::vector<double>> payoff = new double[m][n];
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            payoff[i][j] = Std_random::uniform(-0.5, 0.5);
    test("random " + m + "-by-" + n, payoff);
    return 0;
}