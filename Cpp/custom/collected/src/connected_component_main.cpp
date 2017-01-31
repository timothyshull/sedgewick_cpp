#include <string>

#include "In.h"
#include "Graph.h"
#include "Std_out.h"
#include "Queue.h"
#include "Connected_component.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Graph graph{in};
    Connected_component cc{graph};

    int m{cc.count()};
    Std_out::print_line(std::to_string(m) + " components");

    std::vector<Queue<int>> components;
    components.reserve(static_cast<std::vector<Queue<int>>::size_type>(m));
    for (int i{0}; i < m; ++i) {
        components[i] = Queue<int>{};
    }
    for (int v{0}; v < graph.num_vertices(); ++v) {
        components[cc.id(v)].enqueue(v);
    }

    for (int i{0}; i < m; ++i) {
        for (auto v : components[i]) {
            Std_out::print(std::to_string(v) + " ");
        }
        Std_out::print_line();
    }
    return 0;
}