#include "Static_set_of_ints.h"
#include "utility.h"

Static_set_of_ints::Static_set_of_ints(std::vector<int>& keys) : _set{keys}
{
    std::sort(_set.begin(), _set.end());
    for (int i{1}; i < _set.size(); ++i) {
        if (_set[i] == _set[i - 1]) {
            throw utility::Illegal_argument_exception("Argument vector contains duplicate keys");
        }
    }
}

int Static_set_of_ints::rank(int key)
{
    int lo = 0;
    int hi = _set.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (key < _set[mid]) {
            hi = mid - 1;
        } else if (key > _set[mid]) {
            lo = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}
