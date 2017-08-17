#include "Selection_sort.h"
#include "Std_in.h"

int main()
{
    auto a = Std_in::read_all_strings();
    Selection_sort::sort(a);
    Selection_sort::show(a);
    return 0;
}