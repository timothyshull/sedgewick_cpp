#ifndef STD_STATS_H
#define STD_STATS_H

#include <vector>

namespace Std_stats {
    double max(std::vector<double>& a);

    double max(std::vector<double>& a, int lo, int hi);

    int max(std::vector<int>& a);

    double min(std::vector<double>& a);

    double min(std::vector<double>& a, int lo, int hi);

    int min(std::vector<int>& a);

    double mean(std::vector<double>& a);

    double mean(std::vector<double>& a, int lo, int hi);

    double mean(std::vector<int>& a);

    double var(std::vector<double>& a);

    double var(std::vector<double>& a, int lo, int hi);

    double var(std::vector<int>& a);

    double var_p(std::vector<double>& a);

    double var_p(std::vector<double>& a, int lo, int hi);

    double std_dev(std::vector<double>& a);

    double std_dev(std::vector<double>& a, int lo, int hi);

    double std_dev_p(std::vector<double>& a);

    double std_dev_p(std::vector<double>& a, int lo, int hi);

    double sum(std::vector<double>& a);

    double sum(std::vector<int>& a);

    double sum(std::vector<double>& a, int lo, int hi);

    double plot_points(std::vector<double>& a);

    double plot_lines(std::vector<double>& a);

    double plot_bars(std::vector<double>& a);
};

#endif // STD_STATS_H
