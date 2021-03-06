#include "Binary_out.h"
#include "Binary_in.h"

int main(int argc, char* argv[])
{
    Binary_in in{argv[1]};
    Binary_out out{argv[2]};

    char c;
    while (!in.is_empty()) {
        c = in.read_char();
        out.write(c);
    }
    out.flush();
    return 0;
}