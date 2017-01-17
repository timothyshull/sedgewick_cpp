#include "Digraph.h"
#include "Directed_cycle.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::istream in(argv[1]);
    Digraph g{in};

    Directed_cycle finder{g};
    if (finder.has_cycle()) {
        Std_out::print("Directed cycle: ");
        for (int v : finder.cycle()) {
            Std_out::print(v);
            Std_out::print(" ");
        }
        Std_out::print_line();
    } else {
        Std_out::print_line("No directed cycle");
    }
    Std_out::print_line();
    return 0;
}
