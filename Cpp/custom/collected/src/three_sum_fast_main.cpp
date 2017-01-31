#include "In.h"
#include "Std_out.h"
#include "Three_sum_fast.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    std::vector<int> a{in.read_all_ints()};
    int count{Three_sum_fast::count(a)};
    Std_out::print_line(count);
    return 0;
}