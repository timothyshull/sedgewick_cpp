#include <cmath>
#include "utility.h"
#include "Stopwatch_cpu.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    auto n = utility::str_to_num(argv[1]);

    Stopwatch_cpu timer1{};
    double sum1{0.0};
    for (auto i = 1; i <= n; ++i) {
        sum1 += std::sqrt(i);
    }
    double time1 = timer1.elapsedTime();
    Std_out::printf("%e (%.2f seconds)\n", sum1, time1);

    Stopwatch_cpu timer2{};
    double sum2 = 0.0;
    for (auto i = 1; i <= n; ++i) {
        sum2 += std::pow(i, 0.5);
    }
    double time2 = timer2.elapsedTime();
    Std_out::printf("%e (%.2f seconds)\n", sum2, time2);
    return 0;
}