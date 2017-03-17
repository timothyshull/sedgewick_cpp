#include <string>
#include "Digraph.h"
#include "Std_in.h"
#include "Std_out.h"
#include "Symbol_digraph.h"

int main(int argc, char* argv[])
{
    std::string filename{argv[1]};
    char delimiter = *argv[2];
    Symbol_digraph sg{filename, delimiter};
    Digraph graph = sg.digraph();
    while (!Std_in::is_empty()) {
        std::string t = Std_in::read_line();
        for (auto v : graph.adjacent(sg.index(t))) {
            Std_out::print_line("   " + sg.name(v));
        }
    }
    return 0;
}