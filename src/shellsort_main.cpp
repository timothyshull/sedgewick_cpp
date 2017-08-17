#include "Std_in.h"
#include "Shellsort.h"

int main()
{
    auto a = Std_in::read_all_strings();
    Shellsort::sort(a);
    Shellsort::show(a);
    return 0;
}