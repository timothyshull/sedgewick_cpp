#include "Union_find.h"
#include "Std_in.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    auto n = Std_in::read_int();
    Union_find uf{n};
    while (!Std_in::is_empty()) {
        auto p = Std_in::read_int();
        auto q = Std_in::read_int();
        if (uf.connected(p, q)) { continue; }
        uf.create_union(p, q);
        Std_out::printf("%d %d\n", p, q);
    }
    Std_out::printf("Number of components: %d\n", uf.count());
    return 0;
}
