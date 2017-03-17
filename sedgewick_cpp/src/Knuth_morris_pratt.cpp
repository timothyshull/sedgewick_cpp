#include "Knuth_morris_pratt.h"

Knuth_morris_pratt::Knuth_morris_pratt(std::string& pattern) : _radix{256}, _pattern_string{pattern}
{
    int m = pattern.size();
    _dfa.reserve(_radix);
    for (int i{0}; i < _radix; ++i) {
        _dfa[i].reserve(m);
    }
    _dfa[pattern[0]][0] = 1;
    for (int x{0, j = 1}; j < m; ++j) {
        for (int c{0}; c < _radix; ++c) {
            _dfa[c][j] = _dfa[c][x];
        }
        _dfa[pattern[j]][j] = j + 1;
        x = _dfa[pattern[j]][x];
    }
}

Knuth_morris_pratt::Knuth_morris_pratt(std::vector<char>& pattern, int radix) : _radix{radix}, _pattern_vector{pattern}
{
    int m = pattern.size();
    _dfa.reserve(_radix);
    for (int i{0}; i < _radix; ++i) {
        _dfa[i].reserve(m);
    }
    _dfa[pattern[0]][0] = 1;
    for (int x{0, j = 1}; j < m; ++j) {
        for (int c{0}; c < _radix; ++c) {
            _dfa[c][j] = _dfa[c][x];
        }
        _dfa[pattern[j]][j] = j + 1;
        x = _dfa[pattern[j]][x];
    }
}

int Knuth_morris_pratt::search(std::string& text)
{
    int m = _pattern_string.size();
    int n = text.size();
    int i;
    int j;
    for (i = 0, j = 0; i < n && j < m; ++i) {
        j = _dfa[text[i]][j];
    }
    if (j == m) {
        return i - m;
    }
    return n;
}

int Knuth_morris_pratt::search(std::vector<char>& text)
{
    int m = _pattern_vector.size();
    int n = text.size();
    int i;
    int j;
    for (i = 0, j = 0; i < n && j < m; ++i) {
        j = _dfa[text[i]][j];
    }
    if (j == m) {
        return i - m;
    }
    return n;
}
