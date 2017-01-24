#include "Binary_std_out.h"
#include "Binary_std_in.h"

int main(int argc, char* argv[])
{
    while (!Binary_std_in::is_empty()) {
        char c = Binary_std_in::readChar();
        Binary_std_out::write(c);
    }
    Binary_std_out::flush();
    return 0;
}