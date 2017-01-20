#include "Std_in.h"
#include "Mergesort.h"

int main(int argc, char* argv[])
{
    std::vector<std::string>& a{Std_in::read_all_strings()};
    Mergesort::sort(a);
    Mergesort::show(a);
    return 0;
}