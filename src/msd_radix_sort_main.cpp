#include "Std_in.h"
#include "MSD_radix_sort.h"

int main()
{
    auto a = Std_in::read_all_strings();
    MSD_radix_sort::sort(a);
    MSD_radix_sort::show(a);
    return 0;
}