#include "Three_sum_fast.h"
#include "utility.h"
#include "Std_out.h"

bool ::Three_sum_fast::contains_duplicates(std::vector<int>& a)
{
    for (int i{1}; i < a.size(); ++i) {
        if (a[i] == a[i - 1]) { return true; }
    }
    return false;
}

void ::Three_sum_fast::print_all(std::vector<int>& a)
{
    auto n = a.size();
    std::sort(a.begin(), a.end());
    if (contains_duplicates(a)) { throw utility::Illegal_argument_exception("array contains duplicate integers"); }
    for (int i{0}; i < n; ++i) {
        for (int j{i + 1}; j < n; ++j) {
            int k = std::binary_search(a.begin(), a.end(), -(a[i] + a[j]));
            if (k > j) { Std_out::print_line(std::to_string(a[i]) + " " + std::to_string(a[j]) + " " + std::to_string(a[k])); }
        }
    }
}

int ::Three_sum_fast::count(std::vector<int>& a)
{
    auto n = a.size();
    std::sort(a.begin(), a.end());
    if (contains_duplicates(a)) { throw utility::Illegal_argument_exception("array contains duplicate integers"); }
    int count = 0;
    for (int i{0}; i < n; ++i) {
        for (int j{i + 1}; j < n; ++j) {
            int k = std::binary_search(a.begin(), a.end(), -(a[i] + a[j]));
            if (k > j) { ++count; }
        }
    }
    return count;
}
