// Program 5.7 - Solution to the towers of Hanoi
#include <cstdio>
#include "towers_of_hanoi.h"

void hanoi(int n, int d)
{
    if (n == 0) { return; }
    hanoi(n - 1, -d);
    shift(n, d);
    hanoi(n - 1, -d);
}


void towers_of_hanoi(int n, char from, char to, char aux)
{
    if (n == 1)
    {
        std::printf("\n Move disk 1 from rod %c to rod %c", from, to);
        return;
    }
    towers_of_hanoi(n - 1, from, aux, to);
    std::printf("\n Move disk %d from rod %c to rod %c", n, from, to);
    towers_of_hanoi(n - 1, aux, to, from);
}