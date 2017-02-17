#include "Std_in.h"
#include "Bubblesort.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> a{Std_in::read_all_strings()};
    Bubblesort::sort<std::string>(a);
    Bubblesort::show<std::string>(a);
    return 0;
}