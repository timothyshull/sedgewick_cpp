#include "Queue.h"
#include "Std_out.h"
#include "Digraph.h"
#include "In.h"
#include "Gabow_scc.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Digraph digraph{in};
    Gabow_scc scc{digraph};

    auto m = scc.count();
    Std_out::print_line(m + " components");

    std::vector<Queue<int>> components;
    components.reserve(static_cast<std::vector<Queue<int>>::size_type>(m));
    for (auto i = 0; i < m; ++i) {
        components[i] = Queue<int>{};
    }
    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        components[scc.id(v)].enqueue(v);
    }

    for (auto i = 0; i < m; ++i) {
        for (int v : components[i]) {
            Std_out::print(v + " ");
        }
        Std_out::print_line();
    }
    return 0;
}