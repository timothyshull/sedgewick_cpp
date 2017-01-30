#include "In.h"
#include "Stopwatch.h"
#include "Std_out.h"
#include "Three_sum.h"

int main(int argc, char* argv[])
{
    In in{argv[1]};
    std::vector<int> a{in.readAllInts()};

    Stopwatch timer{};
    int count{Three_sum::count(a)};
    Std_out::print_line("elapsed time = " + std::to_string(timer.elapsed_time()));
    Std_out::print_line(count);
    return 0;
}