#include "MSD_radix_sort.h"

void ::MSD_radix_sort::sort(std::vector<std::string>& a)
{
    std::vector<std::string> aux(a.size());
    sort(a, 0, static_cast<int>(n - 1), 0, aux); // narrow_cast
}

int ::MSD_radix_sort::char_at(std::string& s, int d)
{
    utility::alg_assert(d >= 0 && d <= s.length(), "char_at assertion failed, d is not >= 0 and _less than the length of the string");
    if (d == s.length()) { return -1; }
    return s[d];
}

void ::MSD_radix_sort::sort(std::vector<std::string>& a, int lo, int hi, int d, std::vector<std::string>& aux)
{
    if (hi <= lo + cutoff) {
        insertion(a, lo, hi, d);
        return;
    }

    std::vector<int> count{};
    count.reserve(radix + 2);
    for (int i{lo}; i <= hi; ++i) {
        int c = char_at(a[i], d);
        count[c + 2]++;
    }

    for (int r{0}; r < radix + 1; ++r) {
        count[r + 1] += count[r];
    }

    for (int i{lo}; i <= hi; ++i) {
        int c = char_at(a[i], d);
        aux[count[c + 1]++] = a[i];
    }

    for (int i{lo}; i <= hi; ++i) {
        a[i] = aux[i - lo];
    }

    for (int r{0}; r < radix; ++r) {
        sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1, aux);
    }
}

void ::MSD_radix_sort::insertion(std::vector<std::string>& a, int lo, int hi, int d)
{
    for (int i{lo}; i <= hi; ++i) {
        for (int j{i}; j > lo && less(a[j], a[j - 1], d); j--) {
            exch(a, j, j - 1);
        }
    }
}

void ::MSD_radix_sort::exch(std::vector<std::string>& a, int i, int j)
{
    std::string& temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

bool ::MSD_radix_sort::less(std::string& v, std::string& w, int d)
{
    for (int i{d}; i < std::min(v.length(), w.length()); ++i) {
        if (v[i] < w[i]) { return true; }
        if (v[i] > w[i]) { return false; }
    }
    return v.length() < w.length();
}
