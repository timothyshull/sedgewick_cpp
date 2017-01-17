#include "Std_random.h"
#include "Edge_weighted_digraph.h"
#include "Std_out.h"
#include "Edge_weighted_directed_cycle.h"

int main(int argc, char* argv[])
{

    int num_vertices = atoi(argv[1]);
    int num_edges = atoi(argv[2]);
    int extra_edges = atoi(argv[3]);
    Edge_weighted_digraph g{static_cast<unsigned>(num_vertices)};
    std::vector<int> vertices(static_cast<std::vector<int>::size_type>(num_vertices));
    for (int i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);
    for (int i = 0; i < num_edges; ++i) {
        int v;
        int w;
        do {
            v = Std_random::uniform(num_vertices);
            w = Std_random::uniform(num_vertices);
        } while (v >= w);
        double weight = Std_random::uniform();
        // TODO: add overload of add_edge that constructs the Directed_edge
        g.add_edge(Directed_edge(v, w, weight));
    }

    for (int i = 0; i < extra_edges; ++i) {
        int v = Std_random::uniform(num_vertices);
        int w = Std_random::uniform(num_vertices);
        double weight = Std_random::uniform(0.0, 1.0);
        g.add_edge(v, w, weight);
    }

    Std_out::print_line(g);

    Edge_weighted_directed_cycle finder{g};
    if (finder.has_cycle()) {
        Std_out::print("Cycle: ");
        for (auto e : finder.cycle()) {
            Std_out::print(e);
            Std_out::print(" ");
        }
        Std_out::print_line();
    } else {
        Std_out::print_line("No directed cycle");
    }
    return 0;
}