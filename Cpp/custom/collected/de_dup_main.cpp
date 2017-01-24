#include <string>
#include "Set.h"
#include "Std_in.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    Set<std::string> set{};

    while (!Std_in::is_empty()) {
        std::string key = Std_in::read_string();
        if (!set.contains(key)) {
            set.add(key);
            Std_out::print_line(key);
        }
    }
    return 0;
}