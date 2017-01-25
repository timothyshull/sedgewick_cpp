#include "Out.h"

int main(int argc, char* argv[])
{
    Out out;

    out = Out{};
    out.print_line("Test 1");
    out.close();

    out = Out{"test.txt"};
    out.print_line("Test 2");
    out.close();
    return 0;
}