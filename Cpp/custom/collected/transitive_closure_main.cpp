#include "In.h"
#include "Digraph.h"
#include "Transitive_closure.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    In in{argv[1]};
    Digraph digraph{in};

    Transitive_closure tc{digraph};

    Std_out::print("     ");
    for (int v{0}; v < digraph.num_vertices(); ++v) {
        Std_out::printf("%3d", v);
    }
    Std_out::print_line();
    Std_out::print_line("--------------------------------------------");

    for (int v{0}; v < digraph.num_vertices(); ++v) {
        Std_out::printf("%3d: ", v);
        for (int w{0}; w < digraph.num_vertices(); ++w) {
            if (tc.reachable(v, w)) { Std_out::printf("  T"); }
            else { Std_out::printf("   "); }
        }
        Std_out::print_line();
    }
    return 0;
}