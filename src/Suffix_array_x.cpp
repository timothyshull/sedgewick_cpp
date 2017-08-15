#include "Suffix_array_x.h"
#include "utility.h"

Suffix_array_x::Suffix_array_x(std::string& text)
        : _size{text.size()},
          _text{text + '\0'},
          _index(static_cast<std::vector<int>::size_type>(_size))
{
    for (auto i = 0; i < _size; ++i) {
        _index[i] = i;
    }

    _sort(0, static_cast<int>(_size - 1), 0);
}

int Suffix_array_x::index(int i)
{
    if (i < 0 || i >= _size) { throw utility::Index_out_of_bounds_exception{}; }
    return _index[i];
}

int Suffix_array_x::lcp(int i)
{
    if (i < 1 || i >= _size) { throw utility::Index_out_of_bounds_exception{}; }
    return _lcp(_index[i], _index[i - 1]);
}

std::string Suffix_array_x::select(int i)
{
    if (i < 0 || i >= _size) { throw utility::Index_out_of_bounds_exception{}; }
    return _text.substr(_index[i], _size - _index[i]);
}

int Suffix_array_x::rank(std::string& query)
{
    int lo = 0;
    int hi = static_cast<int>(_size - 1);
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (query < _index[mid]) { hi = mid - 1; }
        else if (_index[mid] < query) { lo = mid + 1; }
        else { return mid; }
    }
    return lo;
}

int Suffix_array_x::rank(std::string&& query)
{
    int lo = 0;
    int hi = static_cast<int>(_size - 1);
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (query < _index[mid]) { hi = mid - 1; }
        else if (_index[mid] < query) { lo = mid + 1; }
        else { return mid; }
    }
    return lo;
}

int Suffix_array_x::operator<(std::string& query, int i)
{
    auto m = query.length();
    int j = 0;
    while (i < _size && j < m) {
        if (query[j] != _text[i]) { return query[j] - _text[i]; }
        ++i;
        ++j;

    }
    if (i < _size) { return -1; }
    if (j < m) { return +1; }
    return 0;
}

void Suffix_array_x::_sort(int lo, int hi, int d)
{
    if (hi <= lo + _cutoff) {
        _insertion(lo, hi, d);
        return;
    }

    int lt = lo, gt = hi;
    char v = _text[_index[lo] + d];
    int i = lo + 1;
    while (i <= gt) {
        char t = _text[_index[i] + d];
        if (t < v) { _exch(lt++, i++); }
        else if (t > v) { _exch(i, gt--); }
        else { ++i; }
    }

    // a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi].
    _sort(lo, lt - 1, d);
    if (v > 0) { _sort(lt, gt, d + 1); }
    _sort(gt + 1, hi, d);
}

void Suffix_array_x::_insertion(int lo, int hi, int d)
{
    for (auto i = lo; i <= hi; ++i) {
        for (auto j = i; j > lo && _less(_index[j], _index[j - 1], d); j--) {
            _exch(j, j - 1);
        }
    }
}

bool Suffix_array_x::_less(int i, int j, int d)
{
    if (i == j) { return false; }
    i = i + d;
    j = j + d;
    while (i < _size && j < _size) {
        if (_text[i] < _text[j]) { return true; }
        if (_text[i] > _text[j]) { return false; }
        ++i;
        ++j;
    }
    return i > j;
}

void Suffix_array_x::_exch(int i, int j)
{
    int swap = _index[i];
    _index[i] = _index[j];
    _index[j] = swap;
}

int Suffix_array_x::_lcp(int i, int j)
{
    int length = 0;
    while (i < _size && j < _size) {
        if (_text[i] != _text[j]) { return length; }
        ++i;
        ++j;
        ++length;
    }
    return length;
}

