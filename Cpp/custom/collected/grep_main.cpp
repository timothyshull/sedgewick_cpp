#include <string>
#include "NFA.h"
#include "Std_in.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::string regexp{"(.*" + std::string{argv[1]} + ".*)"};
    NFA nfa{regexp};
    while (!Std_in::is_empty()) {
        std::string line = Std_in::read_line();
        if (nfa.recognizes(line)) {
            Std_out::print_line(line);
        }
    }
    return 0;
}