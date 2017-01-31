#include "In.h"
#include "Digraph.h"
#include "Std_out.h"
#include "Nonrecursive_directed_dfs.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Digraph digraph{in};
    int s = utility::str_to_num(argv[1]);
    Nonrecursive_directed_dfs dfs{digraph, s};
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (dfs._marked(v)) {
            Std_out::print(v + " ");
        }
    }
    Std_out::print_line();
    return 0;
}