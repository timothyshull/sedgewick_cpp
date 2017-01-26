#include "In.h"
#include "Out.h"

int main(int argc, char* argv[])
{
    Out out{argv[argc - 1]};
    for (int i{1}; i < argc - 1; ++i) {
        In in{argv[i]};
        std::string s{in.readAll()};
        out.print_line(s);
        in.close();
    }
    out.close();
    return 0;
}