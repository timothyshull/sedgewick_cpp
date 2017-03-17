#include <deque>
#include "Std_out.h"
#include "Std_array_io.h"

int main(int argc, char* argv[])
{
    std::vector<double> a{Std_array_io::read_double1D()};
    Std_array_io::print(a);
    Std_out::print_line();

    std::vector<std::vector<double>> b{Std_array_io::read_double2D()};
    Std_array_io::print(b);
    Std_out::print_line();

    std::vector<std::deque<bool>> d{Std_array_io::read_boolean2D()};
    Std_array_io::print(d);
    Std_out::print_line();
    return 0;
}