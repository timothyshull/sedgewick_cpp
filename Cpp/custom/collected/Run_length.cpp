#include "Run_length.h"

void ::Run_length::expand()
{
    bool b = false;
    while (!Binary_std_in::is_empty()) {
        int run = Binary_std_in::read_int(LG_R);
        for (int i = 0; i < run; ++i)
            Binary_std_out::write(b);
        b = !b;
    }
    Binary_std_out::close();
}

void ::Run_length::compress()
{
    char run = 0;
    bool old = false;
    while (!Binary_std_in::is_empty()) {
        bool b = Binary_std_in::read_boolean();
        if (b != old) {
            Binary_std_out::write(run, LG_R);
            run = 1;
            old = !old;
        } else {
            if (run == R - 1) {
                Binary_std_out::write(run, LG_R);
                run = 0;
                Binary_std_out::write(run, LG_R);
            }
            run++;
        }
    }
    Binary_std_out::write(run, LG_R);
    Binary_std_out::close();
}
