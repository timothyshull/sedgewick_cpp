#include <vector>
#include <random>
#include "Rabin_karp.h"

Rabin_karp::Rabin_karp(std::string& pat)
        : _pattern{pat},
          _radix{256},
          _length{pat.size()},
          _prime_num{_long_random_prime()},
          _rm{1}
{
    for (auto i = 1; i <= _length - 1; ++i) {
        _rm = (_radix * _rm) % _prime_num;
    }
    _pattern_hash = _hash(pat, static_cast<int>(_length));
}

int Rabin_karp::search(std::string& txt)
{
    auto n = static_cast<int>(txt.length());
    if (n < _length) { return n; }
    auto text_hash = _hash(txt, static_cast<int>(_length));

    if ((_pattern_hash == text_hash) && _check(txt, 0)) {
        return 0;
    }

    for (auto i = _length; i < n; ++i) {
        text_hash = (text_hash + _prime_num - _rm * txt[i - _length] % _prime_num) % _prime_num;
        text_hash = (text_hash * _radix + txt[i]) % _prime_num;

        auto offset = static_cast<int>(i - _length + 1);
        if ((_pattern_hash == text_hash) && _check(txt, offset)) {
            return offset;
        }
    }

    return n;
}

std::size_t Rabin_karp::_hash(std::string& key, int m)
{
    std::size_t h = 0;
    for (auto j = 0; j < m; ++j) {
        h = (_radix * h + key[j]) % _prime_num;
    }
    return h;
}

bool Rabin_karp::_check(std::string& txt, int i)
{
    for (auto j = 0; j < _length; ++j) {
        if (_pattern[j] != txt[i + j]) {
            return false;
        }
    }
    return true;
}

long Rabin_karp::_long_random_prime()
{
    // simplifies original code -> only would return a prime less than int, may not perform as well
    unsigned max{~0u >> 1};
    max >>= 1;

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<unsigned> dis{0, max};

    unsigned prime_max = dis(gen);
    std::vector<int> primes{prime_max, 1};

    for (auto i = 2; i < prime_max; i++) {
        if (primes[i]) {
            for (int j = i; j * i < prime_max; j++) { primes[i * j] = 0; }
        }
    }

    long prime{2};
    for (auto i = prime_max - 1; i > 2; --i) {
        if (primes[i]) {
            prime = i;
            break;
        }
    }
    return prime;
}
