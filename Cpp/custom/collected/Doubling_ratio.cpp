#include "Doubling_ratio.h"

double ::Doubling_ratio::time_trial(int n)
{
    std::vector<int> a = new int[n];
    for (int i = 0; i < n; ++i) {
        a[i] = Std_random::uniform(-MAXIMUM_INTEGER, MAXIMUM_INTEGER);
    }
    Stopwatch timer = new Stopwatch();
    ThreeSum.count(a);
    return timer.elapsedTime();
}
