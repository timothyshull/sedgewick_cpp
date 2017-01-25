#include <vector>
#include "utility.h"
#include "Std_random.h"
#include "Two_person_zero_sum_game.h"

int main(int argc, char* argv[])
{
    Two_person_zero_sum_game::test1();
    Two_person_zero_sum_game::test2();
    Two_person_zero_sum_game::test3();
    Two_person_zero_sum_game::test4();
    Two_person_zero_sum_game::test5();

    int m = utility::str_to_num(argv[1]);
    int n = utility::str_to_num(argv[2]);
    std::vector<std::vector<double>> payoff;
    payoff.reserve(m);
    for (int i{0}; i < m; ++i) {
        payoff[i] = std::vector<double>{};
        payoff[i].reserve(n);
        for (int j{0}; j < n; ++j) {
            payoff[i][j] = Std_random::uniform(-0.5, 0.5);
        }
    }
    Two_person_zero_sum_game::test("random " + m + "-by-" + n, payoff);
    return 0;
}