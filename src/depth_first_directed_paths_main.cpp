#include "In.h"
#include "Digraph.h"
#include "utility.h"
#include "Depth_first_directed_paths.h"
#include "Std_out.h"

int main(int argc, char *argv[]) {
    In<std::ifstream> in{argv[1]};
    Digraph digraph{in};
    // Std_out::print_line(digraph);

    auto s = utility::str_to_num<int>(argv[1]);
    Depth_first_directed_paths dfs{digraph, s};

    for (auto v = 0; v < digraph.num_vertices(); ++v) {
        if (dfs.has_path_to(v)) {
            Std_out::printf("%d to %d:  ", s, v);
            for (int x : dfs.path_to(v)) {
                if (x == s) Std_out::print(x);
                else Std_out::print("-" + x);
            }
            Std_out::print_line();
        } else {
            Std_out::printf("%d to %d:  not connected\n", s, v);
        }
    }
    return 0;
}