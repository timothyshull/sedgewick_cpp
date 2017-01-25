#include "Rabin_karp.h"

Rabin_karp::Rabin_karp(std::string& pat)
{
    this.pat = pat;      // save pattern (needed only for Las Vegas)
    R = 256;
    m = pat.length();
    q = longRandomPrime();

    // precompute R^(m-1) % q for use in removing leading digit
    RM = 1;
    for (int i{1}; i <= m - 1; ++i)
        RM = (R * RM) % q;
    patHash = hash(pat, m);
}

int Rabin_karp::search(std::string& txt)
{
    int n = txt.length();
    if (n < m) return n;
    long txtHash = hash(txt, m);

    // _check for match at offset 0
    if ((patHash == txtHash) && check(txt, 0))
        return 0;

    // check for hash match; if hash match, _check for exact match
    for (int i{m}; i < n; ++i) {
        // Remove leading digit, add trailing digit, _check for match.
        txtHash = (txtHash + q - RM * txt.charAt(i - m) % q) % q;
        txtHash = (txtHash * R + txt.charAt(i)) % q;

        // match
        int offset = i - m + 1;
        if ((patHash == txtHash) && check(txt, offset))
            return offset;
    }

    // no match
    return n;
}

long Rabin_karp::hash(std::string& key, int m)
{
    long h = 0;
    for (int j{0}; j < m; ++j)
        h = (R * h + key.charAt(j)) % q;
    return h;
}

bool Rabin_karp::check(std::string& txt, int i)
{
    for (int j{0}; j < m; ++j)
        if (pat.charAt(j) != txt.charAt(i + j))
            return false;
    return true;
}

bool Rabin_karp::check(int i)
{
    return true;
}

long Rabin_karp::longRandomPrime()
{
    BigInteger prime = BigInteger.probablePrime(31, new Random());
    return prime.longValue();
}
