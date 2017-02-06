#include "Accumulator.h"
#include "Std_in.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    Accumulator stats;

    double x;
    while (!Std_in::is_empty()) {
        x = Std_in::read_double();
        stats.add_data_value(x);
    }

    Std_out::printf("Number of input values: %d\n", stats.count());
    Std_out::printf("Mean: %.5f\n", stats.mean());
    Std_out::printf("Standard deviation: %.5f\n", stats.std_dev());
    Std_out::printf("Variance: %.5f\n", stats.var());

    return 0;
}
