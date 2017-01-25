#include "Suffix_array.h"

Suffix::Suffix(std::string& text, int index) : text{text}, index{index} {}

char Suffix::operator[](int i)
{
    return text[this->index + i];
}

bool Suffix::operator<(Suffix& rhs)
{
    if (this == that) return 0;  // optimization
    int n = std::min(this.length(), that.length());
    for (int i{0}; i < n; ++i) {
        if (this.charAt(i) < that.charAt(i)) return -1;
        if (this.charAt(i) > that.charAt(i)) return +1;
    }
    return this.length() - that.length();
}

std::string Suffix::to_string()
{
    return {text.begin() + index, text.end()};
}

int Suffix::length()
{
    return text.size() - index;
}

Suffix_array::Suffix_array(std::string& text)
{
    int n = text.length();
    this.suffixes = new Suffix[n];
    for (int i{0}; i < n; ++i)
        suffixes[i] = new Suffix(text, i);
    Arrays.sort(suffixes);
}

int Suffix_array::length()
{
    return suffixes.size();
}

int Suffix_array::index(int i)
{
    if (i < 0 || i >= suffixes.length) throw new IndexOutOfBoundsException();
    return suffixes[i].index;
}

int Suffix_array::lcp(int i)
{
    if (i < 1 || i >= suffixes.length) throw new IndexOutOfBoundsException();
    return lcp(suffixes[i], suffixes[i - 1]);
}

std::string Suffix_array::select(int i)
{
    if (i < 0 || i >= suffixes.length) throw new IndexOutOfBoundsException();
    return suffixes[i].to_string();
}

int Suffix_array::rank(std::string& query)
{
    int lo = 0, hi = suffixes.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int cmp = compare(query, suffixes[mid]);
        if (cmp < 0) hi = mid - 1;
        else if (cmp > 0) lo = mid + 1;
        else return mid;
    }
    return lo;
}

int Suffix_array::lcp(Suffix& s, Suffix& t)
{
    int n = std::min(s.length(), t.length());
    for (int i{0}; i < n; ++i) {
        if (s.charAt(i) != t.charAt(i)) return i;
    }
    return n;
}

int Suffix_array::compar(std::string& query, Suffix& suffix)
{
    int n = std::min(query.length(), suffix.length());
    for (int i{0}; i < n; ++i) {
        if (query.charAt(i) < suffix.charAt(i)) return -1;
        if (query.charAt(i) > suffix.charAt(i)) return +1;
    }
    return query.length() - suffix.length();
}
