#ifndef GAUSSIAN_ELIMINATION_H
#define GAUSSIAN_ELIMINATION_H

#include <vector>

class Gaussian_elimination {
public:
    Gaussian_elimination(std::vector<std::vector<double>>& A, std::vector<double>& b);
    std::vector<double> primal();
    bool isFeasible();
private:
    const static double EPSILON = std::numeric_limits<double>::epsilon();
    const int m;
    const int n;
    std::vector<std::vector<double>> a;

    void forwardElimination();
    void swap(int row1, int row2);
    void pivot(int p, int q);
    bool certifySolution(std::vector<std::vector<double>>& A, std::vector<double>& b);
    void test(std::string& name, std::vector<std::vector<double>>& A, std::vector<double>& b);
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

#endif // GAUSSIAN_ELIMINATION_H
