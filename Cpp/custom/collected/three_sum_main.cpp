#include "In.h"

int main(int argc, char *argv[]) {
    In in{argv[1]};
    std::vector<int> a = in.readAllInts();

    Stopwatch timer = new Stopwatch();
    int count = count(a);
    Std_out::print_line("elapsed time = " + timer.elapsedTime());
    Std_out::print_line(count);
    return 0;
}