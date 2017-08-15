#include "Three_sum.h"
#include "Std_out.h"

void Three_sum::print_all(std::vector<int>& a)
{
    auto n = a.size();
    for (auto i = 0; i < n; ++i) {
        for (auto j = i + 1; j < n; ++j) {
            for (auto k = j + 1; k < n; ++k) {
                if (a[i] + a[j] + a[k] == 0) {
                    Std_out::print_line(std::to_string(a[i]) + " " + std::to_string(a[j]) + " " + std::to_string(a[k]));
                }
            }
        }
    }
}

int Three_sum::count(std::vector<int>& a)
{
    auto n = a.size();
    int count = 0;
    for (auto i = 0; i < n; ++i) {
        for (auto j = i + 1; j < n; ++j) {
            for (auto k = j + 1; k < n; ++k) {
                if (a[i] + a[j] + a[k] == 0) {
                    ++count;
                }
            }
        }
    }
    return count;
}
