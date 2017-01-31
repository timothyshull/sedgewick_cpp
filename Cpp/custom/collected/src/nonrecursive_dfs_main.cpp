#include "Std_out.h"
#include "Graph.h"
#include "In.h"
#include "utility.h"
#include "Nonrecursive_dfs.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Graph graph{in};
    int s = utility::str_to_num(argv[1]);
    Nonrecursive_dfs dfs{graph, s};
    for (int v{0}; v < graph.num_vertices(); ++v) {
        if (dfs.marked(v)) {
            Std_out::print(v + " ");
        }
    }
    Std_out::print_line();
    return 0;
}