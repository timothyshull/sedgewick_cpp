#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <vector>

class Linear_regression {
public:
    Linear_regression(std::vector<double>& x, std::vector<double>& y);
    double intercept();
    double slope();
    double R2();
    double interceptStdErr();
    double slopeStdErr();
    double predict();
    std::string toString();
private:
    const int n;
    const double intercept;
    const double slope;
    const double r2;
    const double svar;
    const double svar0;
    const double svar1;
};

std::ostream& operator<<(std::ostream& os, Linear_regression& out);

#endif // LINEAR_REGRESSION_H
