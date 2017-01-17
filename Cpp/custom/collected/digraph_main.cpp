#include "Digraph.h"
#include "Std_in.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::istringstream s1(argv[1]);
    std::istream in(s1.rdbuf());
    Digraph g{in};
    Std_out::print_line(g);
    return 0;
}
