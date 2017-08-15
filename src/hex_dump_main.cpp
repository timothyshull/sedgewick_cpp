#include "Std_out.h"
#include "Binary_std_in.h"
#include "utility.h"

int main(int argc, char* argv[])
{
    int bytes_per_line = 16;
    if (argc >= 2) {
        bytes_per_line = utility::str_to_num(argv[1]);
    }

    for (auto i = 0; !Binary_std_in::is_empty(); ++i) {
        if (bytes_per_line == 0) {
            Binary_std_in::read_char();
            continue;
        }
        if (i == 0) { Std_out::printf(""); }
        else if (i % bytes_per_line == 0) { Std_out::printf("%d\n", i); }
        else { Std_out::print(" "); }
        char c = Binary_std_in::read_char();
        Std_out::printf("%02x", c & 0xff);
    }
    if (bytes_per_line != 0) { Std_out::print_line(); }
    Std_out::print_line((i * 8) + " bits");
    return 0;
}