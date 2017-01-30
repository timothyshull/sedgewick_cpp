#ifndef TWO_PERSON_ZERO_SUM_GAME_H
#define TWO_PERSON_ZERO_SUM_GAME_H

#include <limits>
#include "Linear_programming.h"

namespace Tpzsg_tests {
    void test(std::string&& description, std::vector<std::vector<double>>& payoff);

    void test1();

    void test2();

    void test3();

    void test4();

    void test5();
}

class Two_person_zero_sum_game {
public:
    Two_person_zero_sum_game(std::vector<std::vector<double>>& payoff);

    double value();

    std::vector<double> row();

    std::vector<double> column();

private:
    const static double _epsilon = std::numeric_limits<double>::epsilon();
    const int _m;
    const int _n;
    Linear_programming _lp;
    double _constant;

    Two_person_zero_sum_game(std::tuple<int, int, Linear_programming, double>&& args);

    double _scale();

    bool _is_primal_feasible();

    bool _is_dual_feasible();

    bool _is_nash_equilibrium(std::vector<std::vector<double>>& payoff);

    bool _certify_solution(std::vector<std::vector<double>>& payoff);

    static std::tuple<int, int, Linear_programming, double> _prep_args(std::vector<std::vector<double>>& payoff);
};

#endif // TWO_PERSON_ZERO_SUM_GAME_H
