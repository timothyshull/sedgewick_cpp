#include "Doubling_test.h"

double ::Doubling_test::timeTrial(int n)
{
    int[] a = new int[n];
    for (int i = 0; i < n; i++) {
        a[i] = StdRandom.uniform(-MAXIMUM_INTEGER, MAXIMUM_INTEGER);
    }
    Stopwatch timer = new Stopwatch();
    ThreeSum.count(a);
    return timer.elapsedTime();
}
