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

    double varp(std::vector<double>& a);

    double varp(std::vector<double>& a, int lo, int hi);

    double stddev(std::vector<double>& a);

    double stddev(std::vector<double>& a, int lo, int hi);

    double stddevp(std::vector<double>& a);

    double stddevp(std::vector<double>& a, int lo, int hi);

    double sum(std::vector<double>& a);

    double sum(std::vector<int>& a);

    double plotPoints(std::vector<double>& a);

    double plotLines(std::vector<double>& a);

    double plotBars(std::vector<double>& a);
};

#endif // STD_STATS_H
