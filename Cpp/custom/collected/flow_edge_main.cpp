#include "Std_out.h"
#include "Flow_edge.h"

int main(int argc, char* argv[])
{
    Flow_edge e{12, 23, 4.56};
    Std_out::print_line(e);
    return 0;
}