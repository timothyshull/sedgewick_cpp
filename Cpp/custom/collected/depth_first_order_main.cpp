#include "Digraph.h"
#include "Depth_first_order.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::istream in{argv[1]};
    Digraph g{in};

    Depth_first_order dfs{g};
    Std_out::print_line("   v  pre post");
    Std_out::print_line("--------------");
    for (int v{0}; v < g.num_vertices(); ++v) {
        Std_out::printf("%4d %4d %4d\n", v, dfs.pre(v), dfs.post(v));
    }

    Std_out::print("Preorder:  ");
    for (int v : dfs.pre()) {
        Std_out::print(v + " ");
    }
    Std_out::print_line();

    Std_out::print("Postorder: ");
    for (int v : dfs.post()) {
        Std_out::print(v + " ");
    }
    Std_out::print_line();

    Std_out::print("Reverse postorder: ");
    for (int v : dfs.reverse_post()) {
        Std_out::print(v + " ");
    }
    Std_out::print_line();
    return 0;
}
