#include "Std_in.h"
#include "Quicksort_3_string.h"

int main()
{
    auto a = Std_in::read_all_strings();
    Quicksort_3_string::sort(a);
    Quicksort_3_string::show(a);
    return 0;
}