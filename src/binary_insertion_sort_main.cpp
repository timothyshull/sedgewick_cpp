#include "Binary_insertion_sort.h"
#include "Std_in.h"

int main()
{
    auto a = Std_in::read_all_strings();
    Binary_insertion_sort::sort(a);
    Binary_insertion_sort::show(a);
    return 0;
}