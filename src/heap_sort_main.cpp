#include "Heap_sort.h"
#include "Std_in.h"

int main()
{
    auto a = Std_in::read_all_strings();
    Heap_sort::sort(a);
    Heap_sort::show(a);
    return 0;
}
