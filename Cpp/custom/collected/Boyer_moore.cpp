#include "Boyer_moore.h"

Boyer_moore::Boyer_moore(std::string& pat)
{
    this.R = 256;
    this.pat = pat;

    // position of rightmost occurrence of c in the pattern
    right = new int[R];
    for (int c = 0; c < R; c++) {
        right[c] = -1;
    }
    for (int j = 0; j < pat.length(); j++) {
        right[pat.charAt(j)] = j;
    }
}

Boyer_moore::Boyer_moore(std::vector<char>& pattern, int R)
{
    this.R = R;
    this.pattern = new char[pattern.length];
    for (int j = 0; j < pattern.length; j++) {
        this.pattern[j] = pattern[j];
    }

    // position of rightmost occurrence of c in the pattern
    right = new int[R];
    for (int c = 0; c < R; c++) {
        right[c] = -1;
    }
    for (int j = 0; j < pattern.length; j++) {
        right[pattern[j]] = j;
    }
}

int Boyer_moore::search(std::string& txt)
{
    int m = pat.length();
    int n = txt.length();
    int skip;
    for (int i = 0; i <= n - m; i += skip) {
        skip = 0;
        for (int j = m - 1; j >= 0; j--) {
            if (pat.charAt(j) != txt.charAt(i + j)) {
                skip = Math.max(1, j - right[txt.charAt(i + j)]);
                break;
            }
        }
        if (skip == 0) { return i; }    // found
    }
    return n;
}

int Boyer_moore::search(std::vector<char>& text)
{
    int m = pattern.length;
    int n = text.length;
    int skip;
    for (int i = 0; i <= n - m; i += skip) {
        skip = 0;
        for (int j = m - 1; j >= 0; j--) {
            if (pattern[j] != text[i + j]) {
                skip = Math.max(1, j - right[text[i + j]]);
                break;
            }
        }
        if (skip == 0) { return i; }    // found
    }
    return n;
}
