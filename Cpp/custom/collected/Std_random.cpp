#include <random>
#include <chrono>
#include <cmath>
#include <sstream>
#include <iostream>

#include "Std_random.h"

namespace Std_random {
    std::random_device rd;

    auto now = std::chrono::system_clock::now();

    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

    auto now_value = now_ms.time_since_epoch();

    std::seed_seq seed;

    void set_seed(long s = static_cast<long>(now_value.count()))
    {
//        std::initializer_list il {s, s + 1, s + 2, s + 3, s + 4};
//        seed{il};
    }

    long get_seed()
    {
        return 0;
    }

    double uniform()
    {
        static std::uniform_real_distribution<double> dist(0, 1);
        return dist(rd);
    }

    int uniform(int n)
    {
        if (n <= 0) {
            throw utility::Illegal_argument_exception("Parameter _n must be positive");
        }
        std::uniform_int_distribution<int> dist(0, n - 1);
        return dist(rd);
    }

    double random()
    {
        return uniform();
    }

    int uniform(int a, int b)
    {
        if (a >= b) {
            throw utility::Illegal_argument_exception("Invalid range");
        }
        if (static_cast<long>(b - a) >= std::numeric_limits<int>::max()) {
            throw utility::Illegal_argument_exception("Invalid range");
        }
        return a + uniform(b - a);
    }

    double uniform(double a, double b)
    {
        if (a >= b) {
            throw utility::Illegal_argument_exception("Invalid range");
        }
        return a + uniform() * (b - a);
    }

    bool bernoulli(double p)
    {
        if (!(p >= 0.0 && p <= 1.0)) {
            throw utility::Illegal_argument_exception("Probability must be between 0.0 and 1.0");
        }
        return uniform() < p;
    }

    bool bernoulli()
    {
        return bernoulli(0.5);
    }

    double gaussian()
    {
        double r;
        double x;
        double y;

        do {
            x = uniform(-1.0, 1.0);
            y = uniform(-1.0, 1.0);
            r = x * x + y * y;
        } while (r >= 1 || r == 0);

        return x * sqrt(-2 * log10(r) / 2);
    }

    double gaussian(double mu, double sigma) { return mu + sigma * gaussian(); }

    int geometric(double p)
    {
        if (!(p >= 0.0 && p <= 1.0)) {
            throw utility::Illegal_argument_exception("Probability must be between 0.0 and 1.0");
        }
        return static_cast<int>(ceil(log10(uniform() / log10(1.0 - p))));
    }

    int poisson(double lambda)
    {
        if (lambda <= 0.0) {
            throw utility::Illegal_argument_exception("Parameter lambda must be positive");
        }
        if (lambda == std::numeric_limits<double>::infinity()) {
            throw utility::Illegal_argument_exception("Parameter lambda must not be infinite");
        }
        int k = 0;
        double p = 1.0;
        double exp_lambda = exp(-lambda);
        do {
            ++k;
            p *= uniform();
        } while (p >= exp_lambda);
        return k - 1;
    }

    double pareto()
    {
        return pareto(1.0);
    }

    double pareto(double alpha)
    {
        if (alpha <= 0.0) {
            throw utility::Illegal_argument_exception("Shape parameter alpha must be positive");
        }
        return pow(1 - uniform(), -1.0 / alpha) - 1.0;
    }

    double cauchy() { return std::tan(pi * (uniform() - 0.5)); }

    int discrete(std::vector<double>& probabilities)
    {
        if (probabilities.empty()) {
            throw utility::Illegal_argument_exception("The \"probabilities\" vector argument cannot be is_empty");
        }
        double epsilon = 1E-14;
        double sum = 0.0;
        int n = probabilities.size();
        for (int i = 0; i < n; ++i) {
            if (probabilities[i] < 0.0) {
                std::stringstream ss;
                ss << "The \"probabilities\" entry " << i << " must be non-negative: " << probabilities[i];
                throw utility::Illegal_argument_exception(ss.str());
            }
            sum += probabilities[i];
        }
        if (sum > 1.0 + epsilon || sum < 1.0 - epsilon) {
            std::stringstream ss;
            ss << "The _sum of the array entries does not approximately equal 1.0: " << sum;
            throw utility::Illegal_argument_exception(ss.str());
        }

        while (true) {
            double r = uniform();
            sum = 0.0;
            for (int i = 0; i < n; ++i) {
                sum = sum + probabilities[i];
                if (sum > r) {
                    return i;
                }
            }
        }
    }

    int discrete(std::vector<int>& frequencies)
    {
        if (frequencies.empty()) {
            throw utility::Illegal_argument_exception("The \"frequencies\" argument vector is null");
        }
        long sum = 0;
        int n = frequencies.size();
        for (int i = 0; i < n; ++i) {
            if (frequencies[i] < 0) {
                std::stringstream ss;
                ss << "The \"frequencies\" vector entry " << i << " must be non-negative: " << frequencies[i];
                throw utility::Illegal_argument_exception(ss.str());
            }
            sum += frequencies[i];
        }
        if (sum == 0) {
            throw utility::Illegal_argument_exception("At least one array entry must be positive");
        }
        if (sum >= std::numeric_limits<int>::max()) {
            throw utility::Illegal_argument_exception("The _sum of \"frequencies\" overflows an the int type");
        }

        double r = uniform(static_cast<int>(sum));
        sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += frequencies[i];
            if (sum > r) {
                return i;
            }
        }

        utility::assert(false, "Unreachable code");
        return -1;
    }

    double exp(double lambda)
    {
        if (lambda <= 0.0) {
            throw utility::Illegal_argument_exception("Rate lambda must be positive");
        }
        return -std::log10(1 - uniform()) / lambda;
    }
}
