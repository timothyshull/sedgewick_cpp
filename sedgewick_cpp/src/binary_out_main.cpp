#include "Binary_out.h"
#include "Binary_in.h"

int main(int argc, char* argv[])
{
    Binary_out out{argv[1]};
    Binary_in in;

    char c;
    while (!in.is_empty()) {
        c = in.read_char();
        out.write(c);
    }
    out.flush();
    return 0;
}