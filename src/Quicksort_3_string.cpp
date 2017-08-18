#include <gsl/gsl_util>

#include "Insertion_sort.h"
#include "Quicksort_3_string.h"
#include "Std_random.h"

void ::Quicksort_3_string::sort(std::vector<std::string> &coll)
{
    Std_random::shuffle(coll);
    sort(coll, 0, gsl::narrow_cast<int>(coll.size()) - 1, 0);
    utility::alg_assert(std::is_sorted(coll.begin(), coll.end()), "Quicksort_3_string is_sorted check failed");
}

int ::Quicksort_3_string::char_at(std::string const &s, int d)
{
    utility::alg_assert(d >= 0 && d <= s.length(), "Quicksort_3_string char_at range check for d failed");
    if (d == s.length()) {
        return -1;
    }
    return s[d];
}

void ::Quicksort_3_string::sort(std::vector<std::string> &a, int lo, int hi, int d)
{
    if (hi <= lo + cutoff) {
        Insertion_sort::sort(a, lo, hi, d);
        return;
    }

    auto lt = lo;
    auto gt = hi;
    auto v = char_at(a[lo], d);
    auto i = lo + 1;
    while (i <= gt) {
        auto t = char_at(a[i], d);
        if (t < v) {
            std::swap(a[lt++], a[i++]);
        } else if (v < t) {
            std::swap(a[i], a[gt--]);
        } else {
            ++i;
        }
    }

    sort(a, lo, lt - 1, d);
    if (v >= 0) {
        sort(a, lt, gt, d + 1);
    }
    sort(a, gt + 1, hi, d);
}

//bool ::Quicksort_3_string::less(std::string &v, std::string w, int d)
//{
//#ifndef NDEBUG
//    utility::alg_assert(
//            v.substr(0, d) == w.substr(0, d),
//            "Quicksort_3_string v and w substring equivalence _check failed"
//    );
//#endif
//    for (auto i = d; i < std::min(v.length(), w.length()); ++i) {
//        if (v[i] < w[i]) {
//            return true;
//        }
//        if (w[i] < v[i]) {
//            return false;
//        }
//    }
//    return v.length() < w.length();
//}
