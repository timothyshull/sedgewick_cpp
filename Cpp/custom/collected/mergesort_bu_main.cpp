#include "Std_in.h"
#include "Mergesort_bu.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> a{Std_in::read_all_strings()};
    Mergesort_bu::sort(a);
    Mergesort_bu::show(a);
    return 0;
}