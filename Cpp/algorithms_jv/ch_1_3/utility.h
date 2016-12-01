#ifndef CH_1_3_UTILITY_H
#define CH_1_3_UTILITY_H

#include <cstdlib>
#include <cstdio>

#define lassert(x, m) ((x) ? (void)0 : (std::fprintf(stderr, "%s\n", m), std::abort()))

class No_such_element_exception : public std::range_error {
public:
    inline explicit No_such_element_exception(const std::string &s) : std::range_error{s} {}

    inline explicit No_such_element_exception(const char *s) : std::range_error{s} {}

    virtual ~No_such_element_exception() noexcept {};
};

#endif //CH_1_3_UTILITY_H
