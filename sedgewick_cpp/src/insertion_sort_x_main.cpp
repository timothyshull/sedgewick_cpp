#include "Std_in.h"
#include "Insertion_sort_x.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> a{Std_in::read_all_strings()};
    Insertion_sort_x::sort(a);
    Insertion_sort_x::show(a);
    return 0;
}