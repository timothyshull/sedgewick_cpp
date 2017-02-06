#include <vector>
#include "Static_set_of_ints.h"
#include "Std_in.h"
#include "Std_out.h"
#include "In.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    std::vector<int> white{in.read_all_ints()};
    Static_set_of_ints set{white};

    int key;
    while (!Std_in::is_empty()) {
        key = Std_in::read_int();
        if (!set.contains(key)) {
            Std_out::print_line(key);
        }
    }
    return 0;
}