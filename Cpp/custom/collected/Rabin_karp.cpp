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
    for (int i{1}; i <= _length - 1; ++i) {
        _rm = (_radix * _rm) % _prime_num;
    }
    _pattern_hash = _hash(pat, static_cast<int>(_length));
}

int Rabin_karp::search(std::string& txt)
{
    int n{static_cast<int>(txt.length())};
    if (n < _length) { return n; }
    auto text_hash = _hash(txt, static_cast<int>(_length));

    if ((_pattern_hash == text_hash) && _check(txt, 0)) {
        return 0;
    }

    for (auto i = _length; i < n; ++i) {
        text_hash = (text_hash + _prime_num - _rm * txt[i - _length] % _prime_num) % _prime_num;
        text_hash = (text_hash * _radix + txt[i]) % _prime_num;

        int offset{static_cast<int>(i - _length + 1)};
        if ((_pattern_hash == text_hash) && _check(txt, offset)) {
            return offset;
        }
    }

    return n;
}

std::size_t Rabin_karp::_hash(std::string& key, int m)
{
    std::size_t h = 0;
    for (int j{0}; j < m; ++j) {
        h = (_radix * h + key[j]) % _prime_num;
    }
    return h;
}

bool Rabin_karp::_check(std::string& txt, int i)
{
    for (int j{0}; j < _length; ++j) {
        if (_pattern[j] != txt[i + j]) {
            return false;
        }
    }
    return true;
}

long Rabin_karp::_long_random_prime()
{
    unsigned max{std::numeric_limits<unsigned>::max()};

    max >>= 1;
    long long prime;
    BigInteger prime = BigInteger.probablePrime(31, new Random());
    return prime.longValue();
}

// from Java BigNumber
static long long smallPrime() {
    int certainty{100};
    int bitLength{31};
    int magLen = (bitLength + 31) >> 5;
    std::vector<int> temp;
    temp.reserve(static_cast<std::vector<int>::size_type>(magLen));
    int highBit = 1 << ((bitLength+31) & 0x1f);
    int highMask = (highBit << 1) - 1;
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    while (true) {
        for (int i=0; i < magLen; i++)
            temp[i] = dis(gen);
        temp[0] = (temp[0] & highMask) | highBit;
        if (bitLength > 2)
            temp[magLen-1] |= 1;  // Make odd if bitlen > 2

        long long p = new BigInteger(temp, 1);

        // Do cheap "pre-test" if applicable
        if (bitLength > 6) {
            long r = p.remainder(SMALL_PRIME_PRODUCT).longValue();
            if ((r%3==0)  || (r%5==0)  || (r%7==0)  || (r%11==0) ||
                (r%13==0) || (r%17==0) || (r%19==0) || (r%23==0) ||
                (r%29==0) || (r%31==0) || (r%37==0) || (r%41==0))
                continue; // Candidate is composite; try another
        }

        // All candidates of bitLength 2 and 3 are prime by this point
        if (bitLength < 4)
            return p;

        // Do expensive test if we survive pre-test (or it's inapplicable)
        if (p.primeToCertainty(certainty, rnd))
            return p;
    }
}
SMALL_PRIME_PRODUCT
= valueOf(3L*5*7*11*13*17*19*23*29*31*37*41);

public BigInteger remainder(BigInteger val) {
    if (val.mag.length < BURNIKEL_ZIEGLER_THRESHOLD ||
        mag.length - val.mag.length < BURNIKEL_ZIEGLER_OFFSET) {
        return remainderKnuth(val);
    } else {
        return remainderBurnikelZiegler(val);
    }
}

static final int BURNIKEL_ZIEGLER_THRESHOLD = 80
static final int BURNIKEL_ZIEGLER_OFFSET = 40;

private BigInteger remainderKnuth(BigInteger val) {
    MutableBigInteger q = new MutableBigInteger(),
            a = new MutableBigInteger(this.mag),
            b = new MutableBigInteger(val.mag);

    return a.divideKnuth(b, q).toBigInteger(this.signum);
}

MutableBigInteger divideKnuth(MutableBigInteger b, MutableBigInteger quotient) {
    return divideKnuth(b,quotient,true);
}

MutableBigInteger divideKnuth(MutableBigInteger b, MutableBigInteger quotient, boolean needRemainder) {
    if (b.intLen == 0)
        throw new ArithmeticException("BigInteger divide by zero");

    // Dividend is zero
    if (intLen == 0) {
        quotient.intLen = quotient.offset = 0;
        return needRemainder ? new MutableBigInteger() : null;
    }

    int cmp = compare(b);
    // Dividend less than divisor
    if (cmp < 0) {
        quotient.intLen = quotient.offset = 0;
        return needRemainder ? new MutableBigInteger(this) : null;
    }
    // Dividend equal to divisor
    if (cmp == 0) {
        quotient.value[0] = quotient.intLen = 1;
        quotient.offset = 0;
        return needRemainder ? new MutableBigInteger() : null;
    }

    quotient.clear();
    // Special case one word divisor
    if (b.intLen == 1) {
        int r = divideOneWord(b.value[b.offset], quotient);
        if(needRemainder) {
            if (r == 0)
                return new MutableBigInteger();
            return new MutableBigInteger(r);
        } else {
            return null;
        }
    }

    // Cancel common powers of two if we're above the KNUTH_POW2_* thresholds
    if (intLen >= KNUTH_POW2_THRESH_LEN) {
        int trailingZeroBits = Math.min(getLowestSetBit(), b.getLowestSetBit());
        if (trailingZeroBits >= KNUTH_POW2_THRESH_ZEROS*32) {
            MutableBigInteger a = new MutableBigInteger(this);
            b = new MutableBigInteger(b);
            a.rightShift(trailingZeroBits);
            b.rightShift(trailingZeroBits);
            MutableBigInteger r = a.divideKnuth(b, quotient);
            r.leftShift(trailingZeroBits);
            return r;
        }
    }

    return divideMagnitude(b, quotient, needRemainder);
}

private BigInteger divideBurnikelZiegler(BigInteger val) {
    return divideAndRemainderBurnikelZiegler(val)[0];
}

/**
 * Calculates {@code this % val} using the Burnikel-Ziegler algorithm.
 * @param val the divisor
 * @return {@code this % val}
 */
private BigInteger remainderBurnikelZiegler(BigInteger val) {
    return divideAndRemainderBurnikelZiegler(val)[1];
}

/**
 * Computes {@code this / val} and {@code this % val} using the
 * Burnikel-Ziegler algorithm.
 * @param val the divisor
 * @return an array containing the quotient and remainder
 */
private BigInteger[] divideAndRemainderBurnikelZiegler(BigInteger val) {
MutableBigInteger q = new MutableBigInteger();
MutableBigInteger r = new MutableBigInteger(this).divideAndRemainderBurnikelZiegler(new MutableBigInteger(val), q);
BigInteger qBigInt = q.isZero() ? ZERO : q.toBigInteger(signum*val.signum);
BigInteger rBigInt = r.isZero() ? ZERO : r.toBigInteger(signum);
return new BigInteger[] {qBigInt, rBigInt};
}
