#include "Weighted_quick_union_uf.h"
#include "Std_in.h"
#include "Std_out.h"

int main()
{
    auto n = Std_in::read_int();
    auto uf = Weighted_quick_union_uf{n};
    while (!Std_in::is_empty()) {
        auto p = Std_in::read_int();
        auto q = Std_in::read_int();
        if (uf.connected(p, q)) {
            continue;
        }
        uf.create_union(p, q);
        Std_out::printf("%d %d\n", p, q);
    }
    Std_out::printf("The number of components is %d\n", uf.count());
    return 0;
}
