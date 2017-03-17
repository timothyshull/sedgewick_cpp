#include <vector>
#include "Doubling_test.h"
#include "Std_random.h"
#include "Stopwatch.h"
#include "Three_sum.h"

double Doubling_test::time_trial(int n)
{
    std::vector<int> a;
    a.reserve(static_cast<std::vector<int>::size_type>(n));
    for (int i{0}; i < n; ++i) {
        a[i] = Std_random::uniform(-max_int, max_int);
    }
    Stopwatch timer;
    Three_sum::count(a);
    return timer.elapsed_time();
}
