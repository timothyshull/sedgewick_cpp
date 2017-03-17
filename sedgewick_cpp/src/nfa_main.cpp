#include <string>
#include "NFA.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::string regexp{"(" + std::string{argv[1]} + ")"};
    std::string txt{argv[2]};
    NFA nfa{regexp};
    Std_out::print_line(nfa.recognizes(txt));
    return 0;
}