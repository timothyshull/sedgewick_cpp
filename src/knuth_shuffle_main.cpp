#include <string>
#include <vector>
#include "Knuth_shuffle.h"
#include "Std_in.h"
#include "Std_out.h"

int main()
{
    std::vector<std::string> a = Std_in::read_all_strings();
    Knuth::shuffle(a);

    for (auto i : a) {
        Std_out::print_line(i);
    }
    return 0;
}
