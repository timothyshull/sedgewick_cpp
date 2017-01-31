#include "Run_length.h"
#include "Binary_std_in.h"
#include "Binary_std_out.h"

void ::Run_length::expand()
{
    bool b = false;
    int run;
    while (!Binary_std_in::is_empty()) {
        run = Binary_std_in::read_int(lg_r);
        for (int i{0}; i < run; ++i) {
            Binary_std_out::write(b);
        }
        b = !b;
    }
    Binary_std_out::close();
}

void ::Run_length::compress()
{
    char run = 0;
    bool old = false;
    bool b;
    while (!Binary_std_in::is_empty()) {
        b = Binary_std_in::read_boolean();
        if (b != old) {
            Binary_std_out::write(run, lg_r);
            run = 1;
            old = !old;
        } else {
            if (run == radix - 1) {
                Binary_std_out::write(run, lg_r);
                run = 0;
                Binary_std_out::write(run, lg_r);
            }
            ++run;
        }
    }
    Binary_std_out::write(run, lg_r);
    Binary_std_out::close();
}
