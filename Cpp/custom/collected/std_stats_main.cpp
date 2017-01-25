#include "Std_out.h"
#include "Std_array_io.h"

int main(int argc, char *argv[]) {
    std::vector<double> a{Std_array_io::read_double1D()};
    Std_out::printf("       min %10.3f\n", Std_array_io::min(a));
    Std_out::printf("      mean %10.3f\n", Std_array_io::mean(a));
    Std_out::printf("       max %10.3f\n", Std_array_io::max(a));
    Std_out::printf("    stddev %10.3f\n", Std_array_io::stddev(a));
    Std_out::printf("       var %10.3f\n", Std_array_io::var(a));
    Std_out::printf("   stddevp %10.3f\n", Std_array_io::stddevp(a));
    Std_out::printf("      varp %10.3f\n", Std_array_io::varp(a));
    return 0;
}