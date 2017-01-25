#include <vector>
#include "Vector.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::vector<double> x_data{1.0, 2.0, 3.0, 4.0};
    std::vector<double> y_data{5.0, 2.0, 4.0, 1.0};
    Vector x{x_data};
    Vector y{y_data};

    Std_out::print_line("   x       = " + x);
    Std_out::print_line("   y       = " + y);

    Vector z = x.plus(y);
    Std_out::print_line("   z       = " + z);

    z = z.times(10.0);
    Std_out::print_line(" 10z       = " + z);

    Std_out::print_line("  |x|      = " + x.magnitude());
    Std_out::print_line(" <x, y>    = " + x.dot(y));
    Std_out::print_line("dist(x, y) = " + x.distanceTo(y));
    Std_out::print_line("dir(x)     = " + x.direction());
    return 0;
}