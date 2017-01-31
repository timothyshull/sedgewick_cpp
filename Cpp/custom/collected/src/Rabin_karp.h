#ifndef RABIN_KARP_H
#define RABIN_KARP_H

#include <string>

class Rabin_karp {
public:
    Rabin_karp(std::string& pat);

    int search(std::string& txt);

private:
    std::string _pattern;
    std::size_t _pattern_hash;
    std::size_t _length;
    long _prime_num;
    int _radix;
    long _rm;

    std::size_t _hash(std::string& key, int m);

    bool _check(std::string& txt, int i);

    inline bool _check(int i) const noexcept { return true; }

    static long _long_random_prime();
};

#endif // RABIN_KARP_H
