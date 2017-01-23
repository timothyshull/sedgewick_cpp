#ifndef LINEAR_PROGRAMMING_H
#define LINEAR_PROGRAMMING_H

#include <limits>
#include <vector>

class Linear_programming {
public:
    Linear_programming(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& c);

    void solve();

    int bland();

    int dantzig();

    int minRatioRule(int q);

    void pivot(int p, int q);

    double value();

    std::vector<double> primal();

    std::vector<double> dual();
private:
    const static double EPSILON = std::numeric_limits<double>::epsilon();
    std::vector<std::vector<int>> a;
    int m;
    int n;
    std::vector<int> basis;

    bool isPrimalFeasible(std::vector<std::vector<double>>& A, std::vector<double>& b);
    bool isDualFeasible(std::vector<std::vector<double>>& A, std::vector<double>& c);
    bool isOptimal(std::vector<double>& b, std::vector<double>& c);
    bool check(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& c);
    void show();
    void test(std::vector<std::vector<double>>& A, std::vector<double>& b, std::vector<double>& c);
    void test1();
    void test2();
    void test3();
    void test4();
};



#endif // LINEAR_PROGRAMMING_H
