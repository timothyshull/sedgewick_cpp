#include "Graph.h"
#include "Std_out.h"
#include "In.h"

int main(int argc, char* argv[])
{
    // In in{argv[1]};
    // Graph g{in};
    Graph g{std::cin};
    Std_out::print_line(g);
    return 0;
}