#include "Std_in.h"
#include "Bubblesort.h"

int main()
{
    auto a = Std_in::read_all_strings();
    Bubblesort::sort(a);
    Bubblesort::show(a);
    return 0;
}