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
    Std_out::print_line("elapsed time = " + timer.elapsedTime());
    Std_out::print_line(count);
    return 0;
}