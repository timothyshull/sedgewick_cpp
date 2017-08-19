#include "Std_random.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    auto n = utility::str_to_num(argv[1]);

    if (argc == 2) {
        double x;
        for (auto i = 0; i < n; ++i) {
            x = Std_random::uniform();
            Std_out::print_line(x);
        }
    } else if (argc == 4) {
        double lo{utility::str_to_num(argv[1])};
        double hi{utility::str_to_num(argv[2])};

        double x;
        for (auto i = 0; i < n; ++i) {
            x = Std_random::uniform(lo, hi);
            Std_out::printf("%.2f\n", x);
        }
    } else {
        throw utility::Illegal_argument_exception{"Invalid number of arguments"};
    }
    return 0;
}