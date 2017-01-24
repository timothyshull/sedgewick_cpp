#include "In.h"
#include "Digraph.h"
#include "utility.h"
#include "Breadth_first_directed_paths.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    In in{argv[1]};
    Digraph g{in};
    Std_out::print_line(g);

    int s = utility::safe_convert_integer(argv[1]);
    Breadth_first_directed_paths bfs{g, s};

    for (int v = 0; v < g.num_vertices(); ++v) {
        if (bfs.has_path_to(v)) {
            Std_out::printf("%d to %d (%d):  ", s, v, bfs.distance_to(v));
            for (int x : bfs.path_to(v)) {
                if (x == s) { Std_out::print(x); }
                else { Std_out::print("->" + x); }
            }
            Std_out::print_line();
        } else {
            Std_out::printf("%d to %d (-):  not connected\n", s, v);
        }

    }
    return 0;
}
