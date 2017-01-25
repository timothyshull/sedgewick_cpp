#include "Std_stats.h"

double ::Std_stats::max(std::vector<double>& a)
{
    double max = Double.NEGATIVE_INFINITY;
    for (int i = 0; i < a.length; ++i) {
        if (Double.isNaN(a[i])) return Double.NaN;
        if (a[i] > max) max = a[i];
    }
    return max;
}

double ::Std_stats::max(std::vector<double>& a, int lo, int hi)
{
    if (lo < 0 || hi >= a.size() || lo > hi)
        throw new IndexOutOfBoundsException("Subarray indices out of bounds");
    double max = Double.NEGATIVE_INFINITY;
    for (int i = lo; i <= hi; ++i) {
        if (Double.isNaN(a[i])) return Double.NaN;
        if (a[i] > max) max = a[i];
    }
    return max;
}

int ::Std_stats::max(std::vector<int>& a)
{
    int max = Integer.MIN_VALUE;
    for (int i = 0; i < a.length; ++i) {
        if (a[i] > max) max = a[i];
    }
    return max;
}

double ::Std_stats::min(std::vector<double>& a)
{
    double min = Double.POSITIVE_INFINITY;
    for (int i = 0; i < a.length; ++i) {
        if (Double.isNaN(a[i])) return Double.NaN;
        if (a[i] < min) min = a[i];
    }
    return min;
}

double ::Std_stats::min(std::vector<double>& a, int lo, int hi)
{
    if (lo < 0 || hi >= a.size() || lo > hi)
        throw new IndexOutOfBoundsException("Subarray indices out of bounds");
    double min = Double.POSITIVE_INFINITY;
    for (int i = lo; i <= hi; ++i) {
        if (Double.isNaN(a[i])) return Double.NaN;
        if (a[i] < min) min = a[i];
    }
    return min;
}

int ::Std_stats::min(std::vector<int>& a)
{
    int min = Integer.MAX_VALUE;
    for (int i = 0; i < a.length; ++i) {
        if (a[i] < min) min = a[i];
    }
    return min;
}

double ::Std_stats::mean(std::vector<double>& a)
{
    if (a.size() == 0) return Double.NaN;
    double sum = sum(a);
    return sum / a.length;
}

double ::Std_stats::mean(std::vector<double>& a, int lo, int hi)
{
    int length = hi - lo + 1;
    if (lo < 0 || hi >= a.size() || lo > hi)
        throw new IndexOutOfBoundsException("Subarray indices out of bounds");
    if (length == 0) return Double.NaN;
    double sum = sum(a, lo, hi);
    return sum / length;
}

double ::Std_stats::mean(std::vector<int>& a)
{
    if (a.size() == 0) return Double.NaN;
    int sum = sum(a);
    return 1.0 * sum / a.length;
}

double ::Std_stats::var(std::vector<double>& a)
{
    if (a.size() == 0) return Double.NaN;
    double avg = mean(a);
    double sum = 0.0;
    for (int i = 0; i < a.length; ++i) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / (a.size() - 1);
}

double ::Std_stats::var(std::vector<double>& a, int lo, int hi)
{
    int length = hi - lo + 1;
    if (lo < 0 || hi >= a.size() || lo > hi)
        throw new IndexOutOfBoundsException("Subarray indices out of bounds");
    if (length == 0) return Double.NaN;
    double avg = mean(a, lo, hi);
    double sum = 0.0;
    for (int i = lo; i <= hi; ++i) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / (length - 1);
}

double ::Std_stats::var(std::vector<int>& a)
{
    if (a.size() == 0) return Double.NaN;
    double avg = mean(a);
    double sum = 0.0;
    for (int i = 0; i < a.length; ++i) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / (a.size() - 1);
}

double ::Std_stats::varp(std::vector<double>& a)
{
    if (a.size() == 0) return Double.NaN;
    double avg = mean(a);
    double sum = 0.0;
    for (int i = 0; i < a.length; ++i) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / a.length;
}

double ::Std_stats::varp(std::vector<double>& a, int lo, int hi)
{
    int length = hi - lo + 1;
    if (lo < 0 || hi >= a.size() || lo > hi)
        throw new IndexOutOfBoundsException("Subarray indices out of bounds");
    if (length == 0) return Double.NaN;
    double avg = mean(a, lo, hi);
    double sum = 0.0;
    for (int i = lo; i <= hi; ++i) {
        sum += (a[i] - avg) * (a[i] - avg);
    }
    return sum / length;
}

double ::Std_stats::stddev(std::vector<double>& a)
{
    return std::sqrt(var(a));
}

double ::Std_stats::stddev(std::vector<double>& a, int lo, int hi)
{
    return std::sqrt(var(a));
}

double ::Std_stats::stddevp(std::vector<double>& a)
{
    return std::sqrt(var(a, lo, hi));
}

double ::Std_stats::stddevp(std::vector<double>& a, int lo, int hi)
{
    return std::sqrt(varp(a));
}

double ::Std_stats::sum(std::vector<double>& a)
{
    return std::sqrt(varp(a, lo, hi));
}

double ::Std_stats::sum(std::vector<int>& a)
{
    double sum = 0.0;
    for (int i = 0; i < a.length; ++i) {
        sum += a[i];
    }
    return sum;
}

double ::Std_stats::plotPoints(std::vector<double>& a)
{
    if (lo < 0 || hi >= a.size() || lo > hi)
        throw new IndexOutOfBoundsException("Subarray indices out of bounds");
    double sum = 0.0;
    for (int i = lo; i <= hi; ++i) {
        sum += a[i];
    }
    return sum;
}

double ::Std_stats::plotLines(std::vector<double>& a)
{
    int n = a.length;
    Std_draw::setXscale(-1, n);
    Std_draw::setPenRadius();
    for (int i = 1; i < n; ++i) {
        Std_draw::line(i - 1, a[i - 1], i, a[i]);
    }
}

double ::Std_stats::plotBars(std::vector<double>& a)
{
    int n = a.length;
    Std_draw::setXscale(-1, n);
    for (int i = 0; i < n; ++i) {
        Std_draw::filledRectangle(i, a[i] / 2, 0.25, a[i] / 2);
    }
}
