#ifndef GAUSS_JORDAN_ELIMINATION_H
#define GAUSS_JORDAN_ELIMINATION_H

#include <limits>
#include <vector>

namespace Gje_tests {
    void test(std::string&& name, std::vector<std::vector<double>>& a, std::vector<double>& b);

    void test1();

    void test2();

    void test3();

    void test4();

    void test5();

    void test6();
}

class Gauss_jordan_elimination {
public:
    Gauss_jordan_elimination(std::vector<std::vector<double>>& a, std::vector<double>& b);

    std::vector<double> primal();

    std::vector<double> dual();

    bool is_feasible();

private:
    const static double _epsilon = std::numeric_limits<double>::epsilon();
    const int _size;
    std::vector<std::vector<double>> _aux;

    void _solve();

    void _swap(int row1, int row2);

    void _pivot(int p, int q);

    void _show();

    bool _certify_solution(std::vector<std::vector<double>>& a, std::vector<double>& b);

};

#endif // GAUSS_JORDAN_ELIMINATION_H
