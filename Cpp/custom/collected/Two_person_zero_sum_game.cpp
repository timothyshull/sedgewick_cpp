#include "Two_person_zero_sum_game.h"
#include "Std_out.h"
#include "utility.h"

Two_person_zero_sum_game::Two_person_zero_sum_game(std::vector<std::vector<double>>& payoff) : Two_person_zero_sum_game{_prep_args(payoff)}
{
    utility::alg_assert(_certify_solution(payoff), "Two_person_zero_sum_game solution certification check failed");
}

double Two_person_zero_sum_game::value()
{
    return 1.0 / _scale() - _constant;
}

std::vector<double> Two_person_zero_sum_game::row()
{
    double scale = _scale();
    std::vector<double> x = _lp.primal();
    for (int j{0}; j < _n; ++j) {
        x[j] /= scale;
    }
    return x;
}

std::vector<double> Two_person_zero_sum_game::column()
{
    double scale = _scale();
    std::vector<double> y = _lp.dual();
    for (int i{0}; i < _m; ++i) {
        y[i] /= scale;
    }
    return y;
}

Two_person_zero_sum_game::Two_person_zero_sum_game(std::tuple<int, int, Linear_programming, double>&& args)
        : _m{std::get<0>(args)},
          _n{std::get<1>(args)},
          _lp{std::get<2>(args)},
          _constant{std::get<3>(args)} {}

double Two_person_zero_sum_game::_scale()
{
    std::vector<double> x = _lp.primal();
    double sum = 0.0;
    for (int j{0}; j < _n; ++j) {
        sum += x[j];
    }
    return sum;
}

bool Two_person_zero_sum_game::_is_primal_feasible()
{
    std::vector<double> x = row();
    double sum = 0.0;
    for (int j{0}; j < _n; ++j) {
        if (x[j] < 0) {
            Std_out::print_line("row vector not a probability distribution");
            Std_out::printf("    x[%d] = %f\n", j, x[j]);
            return false;
        }
        sum += x[j];
    }
    if (std::abs(sum - 1.0) > _epsilon) {
        Std_out::print_line("row vector x[] is not a probability distribution");
        Std_out::print_line("    sum = " + std::to_string(sum));
        return false;
    }
    return true;
}

bool Two_person_zero_sum_game::_is_dual_feasible()
{
    std::vector<double> y = column();
    double sum = 0.0;
    for (int i{0}; i < _m; ++i) {
        if (y[i] < 0) {
            Std_out::print_line("column vector y[] is not a probability distribution");
            Std_out::printf("    y[%d] = %f\n", i, y[i]);
            return false;
        }
        sum += y[i];
    }
    if (std::abs(sum - 1.0) > _epsilon) {
        Std_out::print_line("column vector not a probability distribution");
        Std_out::print_line("    sum = " + std::to_string(sum));
        return false;
    }
    return true;
}

bool Two_person_zero_sum_game::_is_nash_equilibrium(std::vector<std::vector<double>>& payoff)
{
    std::vector<double> x = row();
    std::vector<double> y = column();
    double value = value();

    double opt1 = std::numeric_limits<double>::infinity();
    for (int i{0}; i < _m; ++i) {
        double sum = 0.0;
        for (int j{0}; j < _n; ++j) {
            sum += payoff[i][j] * x[j];
        }
        if (sum > opt1) { opt1 = sum; }
    }
    if (std::abs(opt1 - value) > _epsilon) {
        Std_out::print_line("Optimal value = " + std::to_string(value));
        Std_out::print_line("Optimal best response for column player = " + std::to_string(opt1));
        return false;
    }

    double opt2 = std::numeric_limits<double>::infinity();
    for (int j{0}; j < _n; ++j) {
        double sum = 0.0;
        for (int i{0}; i < _m; ++i) {
            sum += payoff[i][j] * y[i];
        }
        if (sum < opt2) { opt2 = sum; }
    }
    if (std::abs(opt2 - value) > _epsilon) {
        Std_out::print_line("Optimal value = " + std::to_string(value));
        Std_out::print_line("Optimal best response for row player = " + std::to_string(opt2));
        return false;
    }

    return true;
}

bool Two_person_zero_sum_game::_certify_solution(std::vector<std::vector<double>>& payoff)
{
    return _is_primal_feasible() && _is_dual_feasible() && _is_nash_equilibrium(payoff);
}

std::tuple<int, int, Linear_programming, double> Two_person_zero_sum_game::_prep_args(std::vector<std::vector<double>>& payoff)
{
    int m{static_cast<int>(payoff.size())};
    int n{static_cast<int>(payoff[0].size())};
    std::vector<double> c;
    c.reserve(std::vector<double>::size_type(n));
    std::vector<double> b;
    b.reserve(std::vector<double>::size_type(m));
    std::vector<std::vector<double>> a;
    a.reserve(static_cast<std::vector<std::vector<double>>::size_type>(m));
    for (int i{0}; i < m; ++i) {
        a.reserve(static_cast<std::vector<double>::size_type>(n));
    }
    for (int i{0}; i < m; ++i) {
        b[i] = 1.0;
    }
    for (int j{0}; j < n; ++j) {
        c[j] = 1.0;
    }

    double constant = std::numeric_limits<double>::infinity();
    for (int i{0}; i < m; ++i) {
        for (int j{0}; j < n; ++j) {
            if (payoff[i][j] < constant) {
                constant = payoff[i][j];
            }
        }
    }

    if (constant <= 0) { constant = -constant + 1; }
    else { constant = 0; }
    for (int i{0}; i < m; ++i) {
        for (int j{0}; j < n; ++j) {
            a[i][j] = payoff[i][j] + constant;
        }
    }

    Linear_programming lp{a, b, c};
    return {m, n, lp, constant};
}

void Tpzsg_tests::test(std::string&& description, std::vector<std::vector<double>>& payoff)
{
    Std_out::print_line();
    Std_out::print_line(description);
    Std_out::print_line("------------------------------------");
    auto m = payoff.size();
    auto n = payoff[0].size();
    Two_person_zero_sum_game zero_sum_game{payoff};
    std::vector<double> x = zero_sum_game.row();
    std::vector<double> y = zero_sum_game.column();

    Std_out::print("x[] = [");
    for (int j{0}; j < n - 1; ++j) {
        Std_out::printf("%8.4f, ", x[j]);
    }
    Std_out::printf("%8.4f]\n", x[n - 1]);

    Std_out::print("y[] = [");
    for (int i{0}; i < m - 1; ++i) {
        Std_out::printf("%8.4f, ", y[i]);
    }
    Std_out::printf("%8.4f]\n", y[m - 1]);
    Std_out::print_line("value =  " + std::to_string(zero_sum_game.value()));
}

void Tpzsg_tests::test1()
{
    std::vector<std::vector<double>> payoff = {
            {30, -10, 20},
            {10, 20,  -20}
    };
    test("wikipedia", payoff);
}

void Tpzsg_tests::test2()
{
    std::vector<std::vector<double>> payoff = {
            {0,  2,  -3, 0},
            {-2, 0,  0,  3},
            {3,  0,  0,  -4},
            {0,  -3, 4,  0}
    };
    test("Chvatal, p. 230", payoff);
}

void Tpzsg_tests::test3()
{
    std::vector<std::vector<double>> payoff = {
            {0,  2,  -3, 0},
            {-2, 0,  0,  3},
            {3,  0,  0,  -4},
            {0,  -3, 4,  0},
            {0,  0,  -3, 3},
            {-2, 2,  0,  0},
            {3,  -3, 0,  0},
            {0,  0,  4,  -4}
    };
    test("Chvatal, p. 234", payoff);
}

void Tpzsg_tests::test4()
{
    std::vector<std::vector<double>> payoff = {
            {0,  2,  -1, -1},
            {0,  1,  -2, -1},
            {-1, -1, 1,  1},
            {-1, 0,  0,  1},
            {1,  -2, 0,  -3},
            {1,  -1, -1, -3},
            {0,  -3, 2,  -1},
            {0,  -2, 1,  -1},
    };
    test("Chvatal p. 236", payoff);
}

void Tpzsg_tests::test5()
{
    std::vector<std::vector<double>> payoff = {
            {0,  -1, 1},
            {1,  0,  -1},
            {-1, 1,  0}
    };
    test("rock, paper, scisssors", payoff);
}
