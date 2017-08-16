#include "Std_in.h"
#include "Insertion_sort.h"

int main()
{
    auto a = Std_in::read_all_strings();
    Insertion_sort::sort(a);
    Insertion_sort::show(a);
    return 0;
}