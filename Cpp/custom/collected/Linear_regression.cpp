#include "Linear_regression.h"

Linear_regression::Linear_regression(std::vector<double>& x, std::vector<double>& y)
{
    if (x.length != y.length) {
        throw new IllegalArgumentException("array lengths are not equal");
    }
    n = x.length;

    // first pass
    double sumx = 0.0, sumy = 0.0, sumx2 = 0.0;
    for (int i = 0; i < n; i++) {
        sumx += x[i];
        sumx2 += x[i] * x[i];
        sumy += y[i];
    }
    double xbar = sumx / n;
    double ybar = sumy / n;

    // second pass: compute summary statistics
    double xxbar = 0.0, yybar = 0.0, xybar = 0.0;
    for (int i = 0; i < n; i++) {
        xxbar += (x[i] - xbar) * (x[i] - xbar);
        yybar += (y[i] - ybar) * (y[i] - ybar);
        xybar += (x[i] - xbar) * (y[i] - ybar);
    }
    slope = xybar / xxbar;
    intercept = ybar - slope * xbar;

    // more statistical analysis
    double rss = 0.0;      // residual sum of squares
    double ssr = 0.0;      // regression sum of squares
    for (int i = 0; i < n; i++) {
        double fit = slope * x[i] + intercept;
        rss += (fit - y[i]) * (fit - y[i]);
        ssr += (fit - ybar) * (fit - ybar);
    }

    int degreesOfFreedom = n - 2;
    r2 = ssr / yybar;
    svar = rss / degreesOfFreedom;
    svar1 = svar / xxbar;
    svar0 = svar / n + xbar * xbar * svar1;
}

double Linear_regression::intercept()
{
    return intercept;
}

double Linear_regression::slope()
{
    return slope;
}

double Linear_regression::R2()
{
    return r2;
}

double Linear_regression::interceptStdErr()
{
    return Math.sqrt(svar0);
}

double Linear_regression::slopeStdErr()
{
    return Math.sqrt(svar1);
}

double Linear_regression::predict()
{
    return slope * x + intercept;
}

std::string Linear_regression::toString()
{
    String s = "";
    s += String.format("%.2f n + %.2f", slope(), intercept());
    return s + "  (R^2 = " + String.format("%.3f", R2()) + ")";
}

std::ostream& operator<<(std::ostream& os, Linear_regression& out)
{
    return os << out.toString();
}
