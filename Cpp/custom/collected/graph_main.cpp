#include "Graph.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
//    std::istream in{argv[1]};
//    Graph g{in};
    Graph g{std::cin};
    Std_out::print_line(g);
    return 0;
}