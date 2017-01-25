#include "Std_out.h"
#include "Doubling_test.h"

int main(int argc, char *argv[]) {
    for (int n = 250; true; n += n) {
        double time = Doubling_test::time_trial(n);
        Std_out::printf("%7d %5.1f\n", n, time);
    }
    return 0;
}