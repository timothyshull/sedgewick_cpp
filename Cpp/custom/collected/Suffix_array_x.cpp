#include "Suffix_array_x.h"

Suffix_array_x::Suffix_array_x(std::string& text)
{
    n = text.length();
    text = text + '\0';

    this->text = utility::str_to_char_vector(text);
    this.index = new int[n];
    for (int i{0}; i < n; ++i)
        index[i] = i;

    sort(0, n - 1, 0);
}

int Suffix_array_x::length()
{
    return n;
}

int Suffix_array_x::index(int i)
{
    if (i < 0 || i >= n) throw new IndexOutOfBoundsException();
    return index[i];
}

int Suffix_array_x::lcp(int i)
{
    if (i < 1 || i >= n) throw new IndexOutOfBoundsException();
    return lcp(index[i], index[i - 1]);
}

std::string Suffix_array_x::select(int i)
{
    if (i < 0 || i >= n) throw new IndexOutOfBoundsException();
    return new String(text, index[i], n - index[i]);
}

int Suffix_array_x::rank(std::string& query)
{
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int cmp = compare(query, index[mid]);
        if (cmp < 0) hi = mid - 1;
        else if (cmp > 0) lo = mid + 1;
        else return mid;
    }
    return lo;
}

int Suffix_array_x::compare(std::string& query, int i)
{
    int m = query.length();
    int j = 0;
    while (i < n && j < m) {
        if (query.charAt(j) != text[i]) return query.charAt(j) - text[i];
        ++i;
        ++j;

    }
    if (i < n) return -1;
    if (j < m) return +1;
    return 0;
}

void Suffix_array_x::sort(int lo, int hi, int d)
{
    if (hi <= lo + CUTOFF) {
        insertion(lo, hi, d);
        return;
    }

    int lt = lo, gt = hi;
    char v = text[index[lo] + d];
    int i = lo + 1;
    while (i <= gt) {
        char t = text[index[i] + d];
        if (t < v) exch(lt++, i++);
        else if (t > v) exch(i, gt--);
        else ++i;
    }

    // a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi].
    sort(lo, lt - 1, d);
    if (v > 0) sort(lt, gt, d + 1);
    sort(gt + 1, hi, d);
}

void Suffix_array_x::insertion(int lo, int hi, int d)
{
    for (int i{lo}; i <= hi; ++i)
        for (int j{i}; j > lo && less(index[j], index[j - 1], d); j--)
            exch(j, j - 1);
}

bool Suffix_array_x::less(int i, int j, int d)
{
    if (i == j) return false;
    i = i + d;
    j = j + d;
    while (i < n && j < n) {
        if (text[i] < text[j]) return true;
        if (text[i] > text[j]) return false;
        ++i;
        ++j;
    }
    return i > j;
}

void Suffix_array_x::exch(int i, int j)
{
    int swap = index[i];
    index[i] = index[j];
    index[j] = swap;
}

int Suffix_array_x::lcp(int i, int j)
{
    int length = 0;
    while (i < n && j < n) {
        if (text[i] != text[j]) return length;
        ++i;
        ++j;
        ++length;
    }
    return length;
}

