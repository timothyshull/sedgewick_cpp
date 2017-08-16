#include "Mergesort_x.h"
#include "Std_in.h"

int main(int argc, char* argv[])
{
    auto a = Std_in::read_all_strings();
    Mergesort_x::sort(a);
    Mergesort_x::show(a);
    return 0;
}