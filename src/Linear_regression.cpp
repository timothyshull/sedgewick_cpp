#include "Linear_regression.h"
#include "utility.h"

Linear_regression::Linear_regression(std::vector<double>& x, std::vector<double>& y)
{
    if (x.size() != y.size()) {
        throw utility::Illegal_argument_exception("array lengths are not equal");
    }
    _size = static_cast<int>(x.size());

    double sum_x{0.0};
    double sum_y{0.0};
    double sum_x_2{0.0};
    for (auto i = 0; i < _size; ++i) {
        sum_x += x[i];
        sum_x_2 += x[i] * x[i];
        sum_y += y[i];
    }
    double x_bar{sum_x / _size};
    double y_bar{sum_y / _size};

    double xx_bar = 0.0;
    double yy_bar = 0.0;
    double xy_bar = 0.0;
    for (auto i = 0; i < _size; ++i) {
        xx_bar += (x[i] - x_bar) * (x[i] - x_bar);
        yy_bar += (y[i] - y_bar) * (y[i] - y_bar);
        xy_bar += (x[i] - x_bar) * (y[i] - y_bar);
    }
    _slope = xy_bar / xx_bar;
    _intercept = y_bar - _slope * x_bar;

    double rss{0.0};
    double ssr{0.0};
    double fit;
    for (auto i = 0; i < _size; ++i) {
        fit = _slope * x[i] + _intercept;
        rss += (fit - y[i]) * (fit - y[i]);
        ssr += (fit - y_bar) * (fit - y_bar);
    }

    auto degrees_of_freedom = _size - 2;
    _r2 = ssr / yy_bar;
    _s_var = rss / degrees_of_freedom;
    _s_var_1 = _s_var / xx_bar;
    _s_var_0 = _s_var / _size + x_bar * x_bar * _s_var_1;
}

std::string Linear_regression::to_string()
{
    std::stringstream ss;
    ss << _slope << " size " << _intercept << "(R^2 = " << _r2 << ")";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, Linear_regression& out)
{
    return os << out.to_string();
}
