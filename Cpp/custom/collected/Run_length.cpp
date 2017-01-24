#include "Run_length.h"

void ::Run_length::expand()
{
    boolean b = false;
    while (!BinaryStdIn.isEmpty()) {
        int run = BinaryStdIn.readInt(LG_R);
        for (int i = 0; i < run; i++)
            BinaryStdOut.write(b);
        b = !b;
    }
    BinaryStdOut.close();
}

void ::Run_length::compress()
{
    char run = 0;
    boolean old = false;
    while (!BinaryStdIn.isEmpty()) {
        boolean b = BinaryStdIn.readBoolean();
        if (b != old) {
            BinaryStdOut.write(run, LG_R);
            run = 1;
            old = !old;
        } else {
            if (run == R - 1) {
                BinaryStdOut.write(run, LG_R);
                run = 0;
                BinaryStdOut.write(run, LG_R);
            }
            run++;
        }
    }
    BinaryStdOut.write(run, LG_R);
    BinaryStdOut.close();
}
