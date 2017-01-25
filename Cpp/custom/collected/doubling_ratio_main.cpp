#include "Std_out.h"
#include "Doubling_ratio.h"

int main(int argc, char* argv[])
{
    double prev = Doubling_ratio::time_trial(125);
    for (int n{250}; true; n += n) {
        double time = Doubling_ratio::time_trial(n);
        Std_out::printf("%6d %7.1f %5.1f\n", n, time, time / prev);
        prev = time;
    }
    return 0;
}