#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>

#include "Acyclic_lp.h"
#include "Std_out.h"
#include "In.h"

int main(int argc, char* argv[])
{
    In in{argv[1]};
    int s{boost::lexical_cast<int>(argv[2])};
    Edge_weighted_digraph digraph{in};

    Acyclic_lp lp{digraph, s};

    for (int v{0}; v < digraph.num_vertices(); ++v) {
        if (lp.has_path_to(v)) {
            Std_out::printf("%d to %d (%.2f)  ", s, v, lp.distance_to(v));
            for (auto e : lp.path_to(v)) {
                Std_out::print(e.to_string() + "   ");
            }
            Std_out::print_line();
        } else {
            Std_out::printf("%d to %d         no path\n", s, v);
        }
    }

    return 0;
}
