#ifndef TWO_PERSON_ZERO_SUM_GAME_H
#define TWO_PERSON_ZERO_SUM_GAME_H

#include <limits>
#include "Linear_programming.h"

class Two_person_zero_sum_game {
public:
    Two_person_zero_sum_game(std::vector<std::vector<double>>& payoff);

    double value();

    std::vector<double> row();

    std::vector<double> column();

private:
    const static double EPSILON = std::numeric_limits<double>::epsilon();
    const int m;
    const int n;
    Linear_programming lp;
    double constant;

    double scale();

    bool isPrimalFeasible();

    bool isDualFeasible();

    bool isNashEquilibrium(std::vector<std::vector<double>>& payoff);

    bool certifySolution(std::vector<std::vector<double>>& payoff);

    void test(std::string& description, std::vector<std::vector<double>>& payoff);

    void test1();

    void test2();

    void test3();

    void test4();

    void test5();
};

#endif // TWO_PERSON_ZERO_SUM_GAME_H
