#include "Std_out.h"
#include "In.h"
#include "Flow_network.h"

int main(int argc, char* argv[])
{
    In<std::ifstream> in{argv[1]};
    Flow_network network{in};
    Std_out::print_line(network);
    return 0;
}