#include "Binary_out.h"
#include "Binary_in.h"

int main(int argc, char* argv[])
{
    std::string filename = argv[1];
    Binary_out out{filename};
    Binary_in in{};

    while (!in.is_empty()) {
        char c = in.read_char();
        out.write(c);
    }
    out.flush();
    return 0;
}