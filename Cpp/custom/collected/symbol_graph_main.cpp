#include <string>
#include "Symbol_graph.h"
#include "Std_in.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    std::string delimiter = argv[2];
    Symbol_graph sg{filename, delimiter};
    Graph graph{sg.graph()};
    while (!Std_in::is_empty()) {
        std::string source = Std_in::read_line();
        if (sg.contains(source)) {
            int s = sg.index(source);
            for (int v : graph.adj(s)) {
                Std_out::print_line("   " + sg.name(v));
            }
        } else {
            Std_out::print_line("input not contain '" + source + "'");
        }
    }
    return 0;
}