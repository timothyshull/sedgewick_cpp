#include "In.h"
#include "Graph.h"
#include "Cycle.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Graph graph{in};
    Cycle finder{graph};
    if (finder.has_cycle()) {
        for (auto v : finder.cycle()) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    } else {
        Std_out::print_line("Graph is acyclic");
    }
    return 0;
}