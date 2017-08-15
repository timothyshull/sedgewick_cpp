#include "Std_in.h"
#include "Quick_find_uf.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    auto n = Std_in::read_int();
    Quick_find_uf uf{n};
    int p;
    int q;
    while (!Std_in::is_empty()) {
        p = Std_in::read_int();
        q = Std_in::read_int();
        if (uf.connected(p, q)) { continue; }
        uf.create_union(p, q);
        Std_out::print_line(p + " " + q);
    }
    Std_out::print_line(uf.count() + " components");
    return 0;
}