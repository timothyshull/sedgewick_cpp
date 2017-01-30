#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <vector>
#include <cmath>

class Linear_regression {
public:
    Linear_regression(std::vector<double>& x, std::vector<double>& y);

    inline double intercept() const noexcept { return _intercept; };

    inline double slope() const noexcept { return _slope; };

    inline double r2() const noexcept { return _r2; };

    inline double intercept_std_err() const { return std::sqrt(_s_var_0)};

    inline double slope_std_err() const { return std::sqrt(_s_var_1)};

    inline double Linear_regression::predict(double x) const { return _slope * x + _intercept; }

    std::string to_string();

private:
    // all variables are logically const
    int _size;
    double _intercept;
    double _slope;
    double _r2;
    double _s_var;
    double _s_var_0;
    double _s_var_1;
};

std::ostream& operator<<(std::ostream& os, Linear_regression& out);

#endif // LINEAR_REGRESSION_H
