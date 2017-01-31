#include <iostream>

#include "Std_in.h"
#include "Std_out.h"

int main()
{
    Std_out::print_line("Type a string: ");
    std::string s = Std_in::read_string();
    Std_out::print_line("Your string was: " + s);
    Std_out::print_line();

    Std_out::print_line("Type an int: ");
    int a = Std_in::read_int();
    Std_out::printf("Your int was: %d", a);
    Std_out::print_line();

    Std_out::print_line("Type a boolean: ");
    bool b = Std_in::read_boolean();
    Std_out::print("Your boolean was: ");
    Std_out::print_line(b);
    Std_out::print_line();

    Std_out::print_line("Type a double: ");
    double c = Std_in::read_double();
    Std_out::printf("Your double was: %.6f\n", c);
    Std_out::print_line();

    return 0;
}