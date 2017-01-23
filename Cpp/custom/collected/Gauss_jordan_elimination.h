#ifndef GAUSS_JORDAN_ELIMINATION_H
#define GAUSS_JORDAN_ELIMINATION_H

#include <limits>
#include <vector>

class Gauss_jordan_elimination {
public:
    Gauss_jordan_elimination(std::vector<std::vector<double>>& A, std::vector<double>& b);
    std::vector<double> primal();
    std::vector<double> dual();
    bool isFeasible();
private:
    const static double EPSILON = std::numeric_limits<double>::epsilon();
    const int n;
    std::vector<std::vector<double>> a;

    void solve();
    void swap(int row1, int row2);
    void pivot(int p, int q);
    void show();
    bool certifySolution(std::vector<std::vector<double>>& A, std::vector<double>& b);
    void test(std::string& name, std::vector<std::vector<double>>& A, std::vector<double>& b);
    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
};

#endif // GAUSS_JORDAN_ELIMINATION_H
