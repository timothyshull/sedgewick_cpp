#include "Queue.h"
#include "Std_out.h"
#include "Digraph.h"
#include "In.h"
#include "Kosaraju_sharir_scc.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Digraph digraph{in};
    Kosaraju_sharir_scc scc{digraph};

    int m{scc._count()};
    Std_out::print_line(m + " components");

    std::vector<Queue<int>> components;
    components.reserve(m);
    for (int i{0}; i < m; ++i) {
        components[i] = Queue<int>{};
    }
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        components[scc._id(v)].enqueue(v);
    }

    for (int i{0}; i < m; ++i) {
        for (int v : components[i]) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    }
    return 0;
}