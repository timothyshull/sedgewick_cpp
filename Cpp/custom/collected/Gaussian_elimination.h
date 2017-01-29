#ifndef GAUSSIAN_ELIMINATION_H
#define GAUSSIAN_ELIMINATION_H

#include <vector>

namespace Ge_tests {
    void test(std::string&& name, std::vector<std::vector<double>>& a, std::vector<double>& b);

    void test1();

    void test2();

    void test3();

    void test4();

    void test5();

    void test6();

    void test7();

    void test8();

    void test9();
};

class Gaussian_elimination {
public:
    Gaussian_elimination(std::vector<std::vector<double>>& a, std::vector<double>& b);

    std::vector<double> primal();

    bool is_feasible();

private:
    const static double _epsilon = std::numeric_limits<double>::epsilon();
    const int _m;
    const int _n;
    std::vector<std::vector<double>> _a;

    void _forward_elimination();

    void _swap(int row1, int row2);

    void _pivot(int p);

    bool _certify_solution(std::vector<std::vector<double>>& A, std::vector<double>& b);

};

#endif // GAUSSIAN_ELIMINATION_H
