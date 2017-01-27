#include "Std_in.h"
#include "Edge_weighted_digraph.h"
#include "Acyclic_lp.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    int n{Std_in::read_int()};

    int source{2 * n};
    int sink{2 * n + 1};

    Edge_weighted_digraph digraph{2 * n + 2};

    double duration;
    int precedent;
    for (int i{0}; i < n; ++i) {
        duration = Std_in::read_double();
        digraph.add_edge(source, i, 0.0);
        digraph.add_edge(i + n, sink, 0.0);
        digraph.add_edge(i, i + n, duration);

        int m = Std_in::read_int();
        for (int j{0}; j < m; ++j) {
            precedent = Std_in::read_int();
            digraph.add_edge(n + i, precedent, 0.0);
        }
    }

    Acyclic_lp lp{digraph, source};

    Std_out::print_line(" job   _start  finish");
    Std_out::print_line("--------------------");
    for (int i{0}; i < n; ++i) {
        Std_out::printf("%4d %7.1f %7.1f\n", i, lp.distance_to(i), lp.distance_to(i + n));
    }
    Std_out::printf("Finish time: %7.1f\n", lp.distance_to(sink));
    return 0;
}