#include "Std_in.h"
#include "Mergesort.h"

int main()
{
    auto a = Std_in::read_all_strings();
    Mergesort::sort(a);
    Mergesort::show(a);
    return 0;
}