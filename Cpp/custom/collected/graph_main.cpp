#include "Graph.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
//    std::istream _in{argv[1]};
//    Graph g{_in};
    Graph g{std::cin};
    Std_out::print_line(g);
    return 0;
}