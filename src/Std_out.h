#ifndef STD_OUT_H
#define STD_OUT_H

#include <ostream>
#include <vector>
#include <iostream>
#include <fmt/format.h>
#include <fmt/printf.h>

namespace Std_out {
    // alias to format for print and printf
    using fmt::printf;
    using fmt::print;

    template<typename ...Args>
    void print_line(Args &&...args)
    {
        fmt::print(std::forward<Args...>(args)...);
        fmt::print("\n");
    }

    inline void print_line()
    {
        fmt::print("\n");
    }
};

#endif // STD_OUT_H
