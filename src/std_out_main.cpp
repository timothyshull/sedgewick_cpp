#include "Std_out.h"

int main()
{
    Std_out::print_line("Test");
    Std_out::print_line(17);
    Std_out::print_line(true);
    Std_out::printf("%.6f\n", 1.0 / 7.0);
    return 0;
}