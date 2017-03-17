#include "Std_out.h"
#include "utility.h"
#include "Binary_std_in.h"

int main(int argc, char* argv[])
{
    int bits_per_line{16};
    if (argc > 1) {
        bits_per_line = utility::str_to_num(argv[1]);
    }

    int count;
    for (count = 0; !Binary_std_in::is_empty(); ++count) {
        if (bits_per_line == 0) {
            Binary_std_in::read_boolean();
            continue;
        } else if (count != 0 && count % bits_per_line == 0) { Std_out::print_line(); }
        if (Binary_std_in::read_boolean()) { Std_out::print(1); }
        else { Std_out::print(0); }
    }
    if (bits_per_line != 0) { Std_out::print_line(); }
    Std_out::print_line(count + " bits");
    return 0;
}