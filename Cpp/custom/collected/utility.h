#ifndef COLLECTED_UTILITY_H
#define COLLECTED_UTILITY_H

#include<cstdio>
#include<cstdlib>
#include<stdexcept>

namespace utility {
    void assert(bool test, const char msg[]) {
        if (!test) {
            std::fprintf(stderr, "%s\n", msg);
            std::abort();
        }
    }

    class No_such_element_exception : public std::range_error {
    public:
        inline explicit No_such_element_exception(const std::string &s) : std::range_error{s} {}

        inline explicit No_such_element_exception(const char *s) : std::range_error{s} {}

        virtual ~No_such_element_exception() noexcept {};
    };
}

#endif //COLLECTED_UTILITY_H
