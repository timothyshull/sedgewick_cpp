#include "Std_random.h"
#include "Edge_weighted_digraph.h"
#include "Std_out.h"
#include "Edge_weighted_directed_cycle.h"

int main(int argc, char* argv[])
{

    auto num_vertices = utility::str_to_num<int>(argv[1]);
    auto num_edges = utility::str_to_num<int>(argv[2]);
    auto extra_edges = utility::str_to_num<int>(argv[3]);
    Edge_weighted_digraph digraph{num_vertices};
    std::vector<int> vertices;
    vertices.reserve(static_cast<std::vector<int>::size_type>(num_vertices));
    for (auto i = 0; i < num_vertices; ++i) {
        vertices[i] = i;
    }
    Std_random::shuffle(vertices);
    int v;
    int w;
    double weight;
    for (auto i = 0; i < num_edges; ++i) {
        do {
            v = Std_random::uniform(num_vertices);
            w = Std_random::uniform(num_vertices);
        } while (v >= w);
        weight = Std_random::uniform();
        digraph.add_edge(v, w, weight);
    }

    for (auto i = 0; i < extra_edges; ++i) {
        v = Std_random::uniform(num_vertices);
        w = Std_random::uniform(num_vertices);
        weight = Std_random::uniform(0.0, 1.0);
        digraph.add_edge(v, w, weight);
    }

    Std_out::print_line(digraph);

    Edge_weighted_directed_cycle finder{digraph};
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