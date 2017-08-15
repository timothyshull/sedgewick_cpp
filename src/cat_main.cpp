#include "In.h"
#include "Out.h"

int main(int argc, char* argv[])
{
    Out out{argv[argc - 1]};
    for (auto i = 1; i < argc - 1; ++i) {
        In<std::ifstream> in{argv[i]};
        std::string s{in.read_all()};
        out.print_line(s);
        in.close();
    }
    out.close();
    return 0;
}