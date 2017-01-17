#include "utility.h"

namespace utility {
    void assert(bool test, const char msg[])
    {
        if (!test) {
            std::fprintf(stderr, "%s\n", msg);
            std::abort();
        }
    }
}