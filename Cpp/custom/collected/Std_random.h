#ifndef STD_RANDOM_H
#define STD_RANDOM_H

#include <vector>

#include "utility.h"

namespace Std_random {
    constexpr auto pi = 3.14159265358979323846;

    void set_seed(long s);

    long get_seed();

    double uniform();

    int uniform(int n);

    double random();

    int uniform(int a, int b);

    double uniform(double a, double b);

    bool bernoulli(double p);

    bool bernoulli();

    double gaussian();

    double gaussian(double mu, double sigma);

    int geometric(double p);

    int poisson(double lambda);

    double pareto();

    double pareto(double alpha);

    double cauchy();

    int discrete(std::vector<double>& probabilities);

    int discrete(std::vector<int>& frequencies);

    double exp(double lambda);

    template<typename T>
    void shuffle(std::vector<T>& a)
    {
        int n = a.size();
        int r;
        for (int i = 0; i < n; ++i) {
            r = i + uniform(n - i);
            T temp = a[i];
            a[i] = a[r];
            a[r] = temp;
        }
    }

    template<typename T>
    void shuffle(std::vector<T>& a, int lo, int hi)
    {
        int n = a.size();
        if (lo < 0 || lo > hi || hi >= n) {
            throw utility::Index_out_of_bounds_exception("Illegal subarray range");
        }

        int r;
        for (int i = lo; i <= hi; ++i) {
            r = i + uniform(hi - i + 1);
            T temp = a[i];
            a[i] = a[r];
            a[r] = temp;
        }
    }
};

#endif //STD_RANDOM_H
