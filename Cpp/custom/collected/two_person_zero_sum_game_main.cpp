#include <vector>
#include "utility.h"
#include "Std_random.h"
#include "Two_person_zero_sum_game.h"

int main(int argc, char* argv[])
{
    Tpzsg_tests::test1();
    Tpzsg_tests::test2();
    Tpzsg_tests::test3();
    Tpzsg_tests::test4();
    Tpzsg_tests::test5();

    int m{utility::str_to_num(argv[1])};
    int n{utility::str_to_num(argv[2])};
    std::vector<std::vector<double>> payoff;
    payoff.reserve(static_cast<std::vector<std::vector<double>>::size_type>(m));
    for (int i{0}; i < m; ++i) {
        payoff[i] = std::vector<double>{};
        payoff[i].reserve(static_cast<std::vector<double>::size_type>(n));
        for (int j{0}; j < n; ++j) {
            payoff[i][j] = Std_random::uniform(-0.5, 0.5);
        }
    }
    Tpzsg_tests::test("random " + std::to_string(m) + "-by-" + std::to_string(n), payoff);
    return 0;
}