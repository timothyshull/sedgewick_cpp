#include <cmath>

#include "Std_stats.h"
#include "utility.h"
#include "Std_draw.h"

// NOTE: -infinity will just fail to compile if the system cannot handle it
double ::Std_stats::max(std::vector<double>& a)
{
    double max = -std::numeric_limits<double>::infinity();
    for (auto i = 0; i < a.size(); ++i) {
        if (std::isnan(a[i])) { return std::numeric_limits<double>::quiet_NaN(); }
        if (a[i] > max) { max = a[i]; }
    }
    return max;
}

double ::Std_stats::max(std::vector<double>& a, int lo, int hi)
{
    if (lo < 0 || hi >= a.size() || lo > hi) {
        throw utility::Index_out_of_bounds_exception{"Subarray indices out of bounds"};
    };
    double max = -std::numeric_limits<double>::infinity();
    for (auto i = lo; i <= hi; ++i) {
        if (std::isnan(a[i])) { return std::numeric_limits<double>::quiet_NaN(); }
        if (a[i] > max) { max = a[i]; }
    }
    return max;
}

int ::Std_stats::max(std::vector<int>& a)
{
    int max = std::numeric_limits<int>::min();
    for (auto i = 0; i < a.size(); ++i) {
        if (a[i] > max) { max = a[i]; }
    }
    return max;
}

double ::Std_stats::min(std::vector<double>& a)
{
    double min = std::numeric_limits<double>::infinity();
    for (auto i = 0; i < a.size(); ++i) {
        if (std::isnan(a[i])) { return std::numeric_limits<double>::quiet_NaN(); }
        if (a[i] < min) { min = a[i]; }
    }
    return min;
}

double ::Std_stats::min(std::vector<double>& a, int lo, int hi)
{
    if (lo < 0 || hi >= a.size() || lo > hi) {
        throw utility::Index_out_of_bounds_exception{"Subarray indices out of bounds"};
    };
    double min = std::numeric_limits<double>::infinity();
    for (auto i = lo; i <= hi; ++i) {
        if (std::isnan(a[i])) { return std::numeric_limits<double>::quiet_NaN(); }
        if (a[i] < min) { min = a[i]; }
    }
    return min;
}

int ::Std_stats::min(std::vector<int>& a)
{
    int min = std::numeric_limits<int>::max();
    for (auto i = 0; i < a.size(); ++i) {
        if (a[i] < min) { min = a[i]; }
    }
    return min;
}

double ::Std_stats::mean(std::vector<double>& a)
{
    if (a.size() == 0) { return std::numeric_limits<double>::quiet_NaN(); }
    double sum = sum(a);
    return sum / a.size();
}

double ::Std_stats::mean(std::vector<double>& a, int lo, int hi)
{
    int length = hi - lo + 1;
    if (lo < 0 || hi >= a.size() || lo > hi) {
        throw utility::Index_out_of_bounds_exception{"Subarray indices out of bounds"};
    };
    if (length == 0) { return std::numeric_limits<double>::quiet_NaN(); }
    double sum = sum(a, lo, hi);
    return sum / length;
}

double ::Std_stats::mean(std::vector<int>& a)
{
    if (a.size() == 0) { return std::numeric_limits<double>::quiet_NaN(); }
    int sum = sum(a);
    return 1.0 * sum / a.size();
}

double ::Std_stats::var(std::vector<double>& a)
{
    if (a.size() == 0) { return std::numeric_limits<double>::quiet_NaN(); }
    double avg = mean(a);
    double sum = 0.0;
    for (auto i = 0; i < a.size(); ++i) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / (a.size() - 1);
}

double ::Std_stats::var(std::vector<double>& a, int lo, int hi)
{
    int length = hi - lo + 1;
    if (lo < 0 || hi >= a.size() || lo > hi) {
        throw utility::Index_out_of_bounds_exception{"Subarray indices out of bounds"};
    };
    if (length == 0) { return std::numeric_limits<double>::quiet_NaN(); }
    double avg = mean(a, lo, hi);
    double sum = 0.0;
    for (auto i = lo; i <= hi; ++i) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / (length - 1);
}

double ::Std_stats::var(std::vector<int>& a)
{
    if (a.size() == 0) { return std::numeric_limits<double>::quiet_NaN(); }
    double avg = mean(a);
    double sum = 0.0;
    for (auto i = 0; i < a.size(); ++i) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / (a.size() - 1);
}

double ::Std_stats::var_p(std::vector<double>& a)
{
    if (a.size() == 0) { return std::numeric_limits<double>::quiet_NaN(); }
    double avg = mean(a);
    double sum = 0.0;
    for (auto i = 0; i < a.size(); ++i) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / a.size();
}

double ::Std_stats::var_p(std::vector<double>& a, int lo, int hi)
{
    int length = hi - lo + 1;
    if (lo < 0 || hi >= a.size() || lo > hi) {
        throw utility::Index_out_of_bounds_exception{"Subarray indices out of bounds"};
    };
    if (length == 0) { return std::numeric_limits<double>::quiet_NaN(); }
    double avg = mean(a, lo, hi);
    double sum = 0.0;
    for (auto i = lo; i <= hi; ++i) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / length;
}

double ::Std_stats::std_dev(std::vector<double>& a)
{
    return std::sqrt(var(a));
}

double ::Std_stats::std_dev(std::vector<double>& a, int lo, int hi)
{
    return std::sqrt(var(a, lo, hi));
}

double ::Std_stats::std_dev_p(std::vector<double>& a)
{
    return std::sqrt(var_p(a));
}

double ::Std_stats::std_dev_p(std::vector<double>& a, int lo, int hi)
{
    return std::sqrt(var_p(a, lo, hi));
}

double ::Std_stats::sum(std::vector<double>& a)
{
    double sum{0.0};
    for (int i = 0; i < a.size(); ++i) {
        sum += a[i];
    }
    return sum;
}

double ::Std_stats::sum(std::vector<double>& a, int lo, int hi)
{
    if (lo < 0 || hi >= a.size() || lo > hi) {
        throw utility::Index_out_of_bounds_exception{"Subarray indices out of bounds"};
    }
    double sum = 0.0;
    for (int i = lo; i <= hi; i++) {
        sum += a[i];
    }
    return sum;
}

double ::Std_stats::sum(std::vector<int>& a)
{
    double sum = 0.0;
    for (auto i = 0; i < a.size(); ++i) {
        sum += a[i];
    }
    return sum;
}

double ::Std_stats::plot_points(std::vector<double>& a)
{
    auto n = a.size();
    Std_draw::set_x_scale(-1, n);
    Std_draw::set_pen_radius(1.0 / (3.0 * n));
    for (int i = 0; i < n; ++i) {
        Std_draw::point(i, a[i]);
    }
}

double ::Std_stats::plot_lines(std::vector<double>& a)
{
    auto n = a.size();
    Std_draw::set_x_scale(-1, n);
    Std_draw::set_pen_radius();
    for (auto i = 1; i < n; ++i) {
        Std_draw::line(i - 1, a[i - 1], i, a[i]);
    }
}

double ::Std_stats::plot_bars(std::vector<double>& a)
{
    auto n = a.size();
    Std_draw::set_x_scale(-1, n);
    for (auto i = 0; i < n; ++i) {
        Std_draw::filled_rectangle(i, a[i] / 2, 0.25, a[i] / 2);
    }
}
