#include "Mergesort_bu.h"
#include "Std_in.h"

int main() {
    auto a = Std_in::read_all_strings();
    Mergesort_bu::sort(a);
    Mergesort_bu::show(a);
    return 0;
}