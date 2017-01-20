#include "Quicksort_3_string.h"

void ::Quicksort_3_string::sort(std::vector<std::string>& a)
{
    Std_random::shuffle(a);
    sort(a, 0, a.size() - 1, 0);
    utility::assert(is_sorted(a), "Quicksort_3_string is_sorted check failed");
}

int ::Quicksort_3_string::char_at(std::string& s, int d)
{
    utility::assert(d >= 0 && d <= s.length(), "Quicksort_3_string char_at range check for d failed");
    if (d == s.length()) { return -1; }
    return s[d];
}

void ::Quicksort_3_string::sort(std::vector<std::string>& a, int lo, int hi, int d)
{
    if (hi <= lo + cutoff) {
        insertion(a, lo, hi, d);
        return;
    }

    int lt = lo, gt = hi;
    int v = char_at(a[lo], d);
    int i = lo + 1;
    while (i <= gt) {
        int t = char_at(a[i], d);
        if (t < v) { exch(a, lt++, i++); }
        else if (t > v) { exch(a, i, gt--); }
        else { i++; }
    }

    sort(a, lo, lt - 1, d);
    if (v >= 0) { sort(a, lt, gt, d + 1); }
    sort(a, gt + 1, hi, d);
}

void ::Quicksort_3_string::insertion(std::vector<std::string>& a, int lo, int hi, int d)
{
    for (int i = lo; i <= hi; ++i) {
        for (int j = i; j > lo && less(a[j], a[j - 1], d); j--) {
            exch(a, j, j - 1);
        }
    }
}

void ::Quicksort_3_string::exch(std::vector<std::string>& a, int i, int j)
{
    std::string temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

bool ::Quicksort_3_string::less(std::string& v, std::string w, int d)
{
    utility::assert(v.substr(0, d) == w.substr(0, d), "Quicksort_3_string v and w substring equivalence check failed");
    for (int i = d; i < std::min(v.length(), w.length()); ++i) {
        if (v[i] < w[i]) { return true; }
        if (v[i] > w[i]) { return false; }
    }
    return v.length() < w.length();
}

bool ::Quicksort_3_string::is_sorted(std::vector<std::string>& a)
{
    for (int i = 1; i < a.size(); ++i) {
        if (a[i] < a[i - 1]) {
            return false;
        }
    }
    return true;
}
