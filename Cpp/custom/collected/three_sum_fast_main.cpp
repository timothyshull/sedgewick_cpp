#include "In.h"
#include "Std_out.h"
#include "Three_sum_fast.h"

int main(int argc, char* argv[])
{
    In in{argv[1]};
    std::vector<int> a{in.readAllInts()};
    int count{Three_sum_fast::count(a)};
    Std_out::print_line(count);
    return 0;
}