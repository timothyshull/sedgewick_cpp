#include "Heap_sort.h"
#include "Std_in.h"
#include "Std_out.h"
#include "utility.h"

int main()
{
    std::vector<std::string> a{Std_in::read_all_strings()};
    Heap_sort::sort(a);
    Heap_sort::show(a);
    utility::alg_assert(Heap_sort::is_sorted(a), "The Heap_sort is_sorted _check failed");
    return 0;
}
