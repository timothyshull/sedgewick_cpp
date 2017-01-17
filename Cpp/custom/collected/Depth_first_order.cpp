#include "Depth_first_order.h"
#include "Std_out.h"

std::vector<int> Depth_first_order::reverse_post() const
{
    std::vector<int> reverse;
    for (auto v : _postorder) {
        reverse.emplace_back(v);
    }
    return reverse;
}

bool Depth_first_order::_check(Digraph& g)
{
    int r = 0;
    for (int v : post()) {
        if (post(v) != r) {
            Std_out::print_line("post(v) and post() are inconsistent");
            return false;
        }
        r++;
    }

    r = 0;
    for (int v : pre()) {
        if (pre(v) != r) {
            Std_out::print_line("pre(v) and pre() are inconsistent");
            return false;
        }
        r++;
    }

    return true;
}
