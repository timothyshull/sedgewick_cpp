#ifndef LINEAR_PROGRAMMING_H
#define LINEAR_PROGRAMMING_H

#include <limits>
#include <vector>

namespace Lp_tests {
    void test(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& c);

    void test1();

    void test2();

    void test3();

    void test4();
}

class Linear_programming {
public:
    Linear_programming(std::vector<std::vector<double>>& a, std::vector<double>& b, std::vector<double>& c);

    void solve();

    int bland();

    int dantzig();

    int min_ratio_rule(int q);

    void pivot(int p, int q);

    double value();

    std::vector<double> primal();

    std::vector<double> dual();

private:
    const static double _epsilon = std::numeric_limits<double>::epsilon();
    std::vector<std::vector<double>> _aux;
    int _m;
    int _n;
    std::vector<int> _basis;

    bool _is_primal_feasible(std::vector<std::vector<double>>& a, std::vector<double>& b);

    bool _is_dual_feasible(std::vector<std::vector<double>>& A, std::vector<double>& c);

    bool _is_optimal(std::vector<double>& b, std::vector<double>& c);

    bool _check(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& c);

    void _show();
};

#endif // LINEAR_PROGRAMMING_H
