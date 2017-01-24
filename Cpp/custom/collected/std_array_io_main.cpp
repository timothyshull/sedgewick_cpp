#include "Std_out.h"

int main(int argc, char *argv[]) {
    std::vector<double> a = StdArrayIO.read_double1D();
    StdArrayIO.print(a);
    Std_out::print_line();

    std::vector<std::vector<double>> b = StdArrayIO.read_double2D();
    StdArrayIO.print(b);
    Std_out::print_line();

    std::vector<std::deque<bool>> d = StdArrayIO.read_boolean2D();
    StdArrayIO.print(d);
    Std_out::print_line();
    return 0;
}