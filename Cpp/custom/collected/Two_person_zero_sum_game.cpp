#include "Two_person_zero_sum_game.h"

Two_person_zero_sum_game::Two_person_zero_sum_game(std::vector<std::vector<double>>& payoff)
{
    m = payoff.length;
    n = payoff[0].length;

    double[] c = new double[n];
    double[] b = new double[m];
    double[][] A = new double[m][n];
    for (int i = 0; i < m; i++)
        b[i] = 1.0;
    for (int j = 0; j < n; j++)
        c[j] = 1.0;

    // find smallest entry
    constant = Double.POSITIVE_INFINITY;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (payoff[i][j] < constant)
                constant = payoff[i][j];

    // add constant  to every entry to make strictly positive
    if (constant <= 0) constant = -constant + 1;
    else constant = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
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
    double[] x = lp.primal();
    for (int j = 0; j < n; j++)
        x[j] /= scale;
    return x;
}

std::vector<double> Two_person_zero_sum_game::column()
{
    double scale = scale();
    double[] y = lp.dual();
    for (int i = 0; i < m; i++)
        y[i] /= scale;
    return y;
}

double Two_person_zero_sum_game::scale()
{
    double[] x = lp.primal();
    double sum = 0.0;
    for (int j = 0; j < n; j++)
        sum += x[j];
    return sum;
}

bool Two_person_zero_sum_game::isPrimalFeasible()
{
    double[] x = row();
    double sum = 0.0;
    for (int j = 0; j < n; j++) {
        if (x[j] < 0) {
            StdOut.println("row vector not a probability distribution");
            StdOut.printf("    x[%d] = %f\n", j, x[j]);
            return false;
        }
        sum += x[j];
    }
    if (Math.abs(sum - 1.0) > EPSILON) {
        StdOut.println("row vector x[] is not a probability distribution");
        StdOut.println("    sum = " + sum);
        return false;
    }
    return true;
}

bool Two_person_zero_sum_game::isDualFeasible()
{
    double[] y = column();
    double sum = 0.0;
    for (int i = 0; i < m; i++) {
        if (y[i] < 0) {
            StdOut.println("column vector y[] is not a probability distribution");
            StdOut.printf("    y[%d] = %f\n", i, y[i]);
            return false;
        }
        sum += y[i];
    }
    if (Math.abs(sum - 1.0) > EPSILON) {
        StdOut.println("column vector not a probability distribution");
        StdOut.println("    sum = " + sum);
        return false;
    }
    return true;
}

bool Two_person_zero_sum_game::isNashEquilibrium(std::vector<std::vector<double>>& payoff)
{
    double[] x = row();
    double[] y = column();
    double value = value();

    // given row player's mixed strategy, find column player's best pure strategy
    double opt1 = Double.NEGATIVE_INFINITY;
    for (int i = 0; i < m; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += payoff[i][j] * x[j];
        }
        if (sum > opt1) opt1 = sum;
    }
    if (Math.abs(opt1 - value) > EPSILON) {
        StdOut.println("Optimal value = " + value);
        StdOut.println("Optimal best response for column player = " + opt1);
        return false;
    }

    // given column player's mixed strategy, find row player's best pure strategy
    double opt2 = Double.POSITIVE_INFINITY;
    for (int j = 0; j < n; j++) {
        double sum = 0.0;
        for (int i = 0; i < m; i++) {
            sum += payoff[i][j] * y[i];
        }
        if (sum < opt2) opt2 = sum;
    }
    if (Math.abs(opt2 - value) > EPSILON) {
        StdOut.println("Optimal value = " + value);
        StdOut.println("Optimal best response for row player = " + opt2);
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
    StdOut.println();
    StdOut.println(description);
    StdOut.println("------------------------------------");
    int m = payoff.length;
    int n = payoff[0].length;
    TwoPersonZeroSumGame zerosum = new TwoPersonZeroSumGame(payoff);
    double[] x = zerosum.row();
    double[] y = zerosum.column();

    StdOut.print("x[] = [");
    for (int j = 0; j < n - 1; j++)
        StdOut.printf("%8.4f, ", x[j]);
    StdOut.printf("%8.4f]\n", x[n - 1]);

    StdOut.print("y[] = [");
    for (int i = 0; i < m - 1; i++)
        StdOut.printf("%8.4f, ", y[i]);
    StdOut.printf("%8.4f]\n", y[m - 1]);
    StdOut.println("value =  " + zerosum.value());
}

void Two_person_zero_sum_game::test1()
{
    double[][] payoff = {
            {30, -10, 20},
            {10, 20, -20}
    };
    test("wikipedia", payoff);
}

void Two_person_zero_sum_game::test2()
{
    double[][] payoff = {
            {0, 2, -3, 0},
            {-2, 0, 0, 3},
            {3, 0, 0, -4},
            {0, -3, 4, 0}
    };
    test("Chvatal, p. 230", payoff);
}

void Two_person_zero_sum_game::test3()
{
    double[][] payoff = {
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
    double[][] payoff = {
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
    double[][] payoff = {
            {0, -1, 1},
            {1, 0, -1},
            {-1, 1, 0}
    };
    test("rock, paper, scisssors", payoff);
}
