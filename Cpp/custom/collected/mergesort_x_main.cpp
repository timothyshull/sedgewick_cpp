#include "Std_in.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> a{Std_in::read_all_strings()};
    Mergersort_x::sort(a);
    Mergersort_x::show(a);
    return 0;
}