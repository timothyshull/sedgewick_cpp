#include "Two_person_zero_sum_game.h"

Two_person_zero_sum_game::Two_person_zero_sum_game(std::vector<std::vector<double>>& payoff)
{
    m = payoff.length;
    n = payoff[0].length;

    std::vector<double> c = new double[n];
    std::vector<double> b = new double[m];
    std::vector<std::vector<double>> A = new double[m][n];
    for (int i{0}; i < m; ++i)
        b[i] = 1.0;
    for (int j{0}; j < n; ++j)
        c[j] = 1.0;

    // find smallest entry
    constant = Double.POSITIVE_INFINITY;
    for (int i{0}; i < m; ++i)
        for (int j{0}; j < n; ++j)
            if (payoff[i][j] < constant)
                constant = payoff[i][j];

    // add constant  to every entry to make strictly positive
    if (constant <= 0) constant = -constant + 1;
    else constant = 0;
    for (int i{0}; i < m; ++i)
        for (int j{0}; j < n; ++j)
            A[i][j] = payoff[i][j] + constant;

    lp = new LinearProgramming(A, b, c);

    assert certifySolution(payoff);
}

double Two_person_zero_sum_game::value()
{
    return 1.0 / scale() - constant;
}

std::vector<double> Two_person_zero_sum_game::row()
{
    double scale = scale();
    std::vector<double> x = lp.primal();
    for (int j{0}; j < n; ++j)
        x[j] /= scale;
    return x;
}

std::vector<double> Two_person_zero_sum_game::column()
{
    double scale = scale();
    std::vector<double> y = lp.dual();
    for (int i{0}; i < m; ++i)
        y[i] /= scale;
    return y;
}

double Two_person_zero_sum_game::scale()
{
    std::vector<double> x = lp.primal();
    double sum = 0.0;
    for (int j{0}; j < n; ++j)
        sum += x[j];
    return sum;
}

bool Two_person_zero_sum_game::isPrimalFeasible()
{
    std::vector<double> x = row();
    double sum = 0.0;
    for (int j{0}; j < n; ++j) {
        if (x[j] < 0) {
            Std_out::print_line("row vector not a probability distribution");
            Std_out::printf("    x[%d] = %f\n", j, x[j]);
            return false;
        }
        sum += x[j];
    }
    if (std::abs(sum - 1.0) > EPSILON) {
        Std_out::print_line("row vector x[] is not a probability distribution");
        Std_out::print_line("    sum = " + sum);
        return false;
    }
    return true;
}

bool Two_person_zero_sum_game::isDualFeasible()
{
    std::vector<double> y = column();
    double sum = 0.0;
    for (int i{0}; i < m; ++i) {
        if (y[i] < 0) {
            Std_out::print_line("column vector y[] is not a probability distribution");
            Std_out::printf("    y[%d] = %f\n", i, y[i]);
            return false;
        }
        sum += y[i];
    }
    if (std::abs(sum - 1.0) > EPSILON) {
        Std_out::print_line("column vector not a probability distribution");
        Std_out::print_line("    sum = " + sum);
        return false;
    }
    return true;
}

bool Two_person_zero_sum_game::isNashEquilibrium(std::vector<std::vector<double>>& payoff)
{
    std::vector<double> x = row();
    std::vector<double> y = column();
    double value = value();

    // given row player's mixed strategy, find column player's best pure strategy
    double opt1 = Double.NEGATIVE_INFINITY;
    for (int i{0}; i < m; ++i) {
        double sum = 0.0;
        for (int j{0}; j < n; ++j) {
            sum += payoff[i][j] * x[j];
        }
        if (sum > opt1) opt1 = sum;
    }
    if (std::abs(opt1 - value) > EPSILON) {
        Std_out::print_line("Optimal value = " + value);
        Std_out::print_line("Optimal best response for column player = " + opt1);
        return false;
    }

    // given column player's mixed strategy, find row player's best pure strategy
    double opt2 = Double.POSITIVE_INFINITY;
    for (int j{0}; j < n; ++j) {
        double sum = 0.0;
        for (int i{0}; i < m; ++i) {
            sum += payoff[i][j] * y[i];
        }
        if (sum < opt2) opt2 = sum;
    }
    if (std::abs(opt2 - value) > EPSILON) {
        Std_out::print_line("Optimal value = " + value);
        Std_out::print_line("Optimal best response for row player = " + opt2);
        return false;
    }


    return true;
}

bool Two_person_zero_sum_game::certifySolution(std::vector<std::vector<double>>& payoff)
{
    return isPrimalFeasible() && isDualFeasible() && isNashEquilibrium(payoff);
}

void Two_person_zero_sum_game::test(std::string& description, std::vector<std::vector<double>>& payoff)
{
    Std_out::print_line();
    Std_out::print_line(description);
    Std_out::print_line("------------------------------------");
    int m = payoff.length;
    int n = payoff[0].length;
    TwoPersonZeroSumGame zerosum = new TwoPersonZeroSumGame(payoff);
    std::vector<double> x = zerosum.row();
    std::vector<double> y = zerosum.column();

    Std_out::print("x[] = [");
    for (int j{0}; j < n - 1; ++j)
        Std_out::printf("%8.4f, ", x[j]);
    Std_out::printf("%8.4f]\n", x[n - 1]);

    Std_out::print("y[] = [");
    for (int i{0}; i < m - 1; ++i)
        Std_out::printf("%8.4f, ", y[i]);
    Std_out::printf("%8.4f]\n", y[m - 1]);
    Std_out::print_line("value =  " + zerosum.value());
}

void Two_person_zero_sum_game::test1()
{
    std::vector<std::vector<double>> payoff = {
            {30, -10, 20},
            {10, 20, -20}
    };
    test("wikipedia", payoff);
}

void Two_person_zero_sum_game::test2()
{
    std::vector<std::vector<double>> payoff = {
            {0, 2, -3, 0},
            {-2, 0, 0, 3},
            {3, 0, 0, -4},
            {0, -3, 4, 0}
    };
    test("Chvatal, p. 230", payoff);
}

void Two_person_zero_sum_game::test3()
{
    std::vector<std::vector<double>> payoff = {
            {0, 2, -3, 0},
            {-2, 0, 0, 3},
            {3, 0, 0, -4},
            {0, -3, 4, 0},
            {0, 0, -3, 3},
            {-2, 2, 0, 0},
            {3, -3, 0, 0},
            {0, 0, 4, -4}
    };
    test("Chvatal, p. 234", payoff);
}

void Two_person_zero_sum_game::test4()
{
    std::vector<std::vector<double>> payoff = {
            {0, 2, -1, -1},
            {0, 1, -2, -1},
            {-1, -1, 1, 1},
            {-1, 0, 0, 1},
            {1, -2, 0, -3},
            {1, -1, -1, -3},
            {0, -3, 2, -1},
            {0, -2, 1, -1},
    };
    test("Chvatal p. 236", payoff);
}

void Two_person_zero_sum_game::test5()
{
    std::vector<std::vector<double>> payoff = {
            {0, -1, 1},
            {1, 0, -1},
            {-1, 1, 0}
    };
    test("rock, paper, scisssors", payoff);
}
