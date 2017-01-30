#include <string>
#include "Graph.h"
#include "Symbol_graph.h"
#include "Std_out.h"
#include "Std_in.h"
#include "Breadth_first_paths.h"

int main(int argc, char* argv[])
{
    std::string filename{argv[1]};
    std::string delimiter{argv[2]};
    std::string source{argv[3]};

    // Std_out::print_line("Source: " + source);

    Symbol_graph sg{filename, delimiter};
    Graph graph{sg._graph()};
    if (!sg.contains(source)) {
        Std_out::print_line(source + " not _in database.");
        return -1;
    }

    int s{sg.index_of(source)};
    Breadth_first_paths bfs{graph, s};

    while (!Std_in::is_empty()) {
        std::string sink = Std_in::read_line();
        if (sg.contains(sink)) {
            int t = sg.index_of(sink);
            if (bfs.has_path_to(t)) {
                for (int v : bfs.path_to(t)) {
                    Std_out::print_line("   " + sg.nameOf(v));
                }
            } else {
                Std_out::print_line("Not connected");
            }
        } else {
            Std_out::print_line("   Not _in database.");
        }
    }
    return 0;
}