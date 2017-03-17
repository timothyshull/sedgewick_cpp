#include <string>
#include "Topological.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::string filename{argv[1]};
    std::string delimiter{argv[2]};
    Symbol_digraph sg{filename, delimiter};
    Topological topological{sg.digraph()};
    for (int v : topological.order()) {
        Std_out::print_line(sg.name_of(v));
    }
    return 0;
}