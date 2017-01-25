#include "Three_sum.h"

void Three_sum::printAll(std::vector<int>& a)
{
    int n = a.length;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (a[i] + a[j] + a[k] == 0) {
                    Std_out::print_line(a[i] + " " + a[j] + " " + a[k]);
                }
            }
        }
    }
}

int Three_sum::count(std::vector<int>& a)
{
    int n = a.length;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (a[i] + a[j] + a[k] == 0) {
                    ++count;
                }
            }
        }
    }
    return count;
}
