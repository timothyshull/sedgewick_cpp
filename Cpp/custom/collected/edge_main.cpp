#include "Std_out.h"
#include "Edge.h"

int main(int argc, char* argv[])
{
    Edge e{12, 34, 5.67};
    Std_out::print_line(e);
    return 0;
}