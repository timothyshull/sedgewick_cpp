#include "Doubling_ratio.h"

double ::Doubling_ratio::timeTrial(int n)
{
    int[] a = new int[n];
    for (int i = 0; i < n; i++) {
        a[i] = StdRandom.uniform(-MAXIMUM_INTEGER, MAXIMUM_INTEGER);
    }
    Stopwatch timer = new Stopwatch();
    ThreeSum.count(a);
    return timer.elapsedTime();
}
