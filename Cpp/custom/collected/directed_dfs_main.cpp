#include "Digraph.h"
#include "In.h"
#include "Directed_dfs.h"
#include "utility.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    In in{argv[1]};
    Digraph digraph{in};

    std::vector<int> sources;
    sources.reserve(argc - 2);
    int s;
    for (int i = 2; i < argc; ++i) {
        s = utility::safe_convert_integer(argv[i]);
        sources.push_back(s);
    }

    Directed_dfs dfs{digraph, sources};

    for (int v = 0; v < digraph.num_vertices(); ++v) {
        if (dfs.marked(v)) { Std_out::print(v + " "); }
    }
    Std_out::print_line();
    return 0;
}