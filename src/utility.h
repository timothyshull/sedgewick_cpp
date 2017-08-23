#ifndef UTILITY_H
#define UTILITY_H

//#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <memory>
#include <string>
#include <ios>
#include <type_traits>
#include <iostream>
#include <vector>
#include <sstream>

#include <fmt/printf.h>

namespace utility {
    const static int max_num_str_len = 25;

    class Bad_lexical_cast : public std::bad_cast {
    public:
        explicit Bad_lexical_cast(std::string s) : _what{std::move(s)} {}

        explicit Bad_lexical_cast(char *const s) : _what{s} {}

    private:
        std::string _what;
    };

    class No_such_element_exception : public std::range_error {
    public:
        explicit No_such_element_exception(std::string const &s) : std::range_error{s} {}

        explicit No_such_element_exception(char const *s) : std::range_error{s} {}
    };

    class Illegal_argument_exception : public std::invalid_argument {
    public:
        inline explicit Illegal_argument_exception(std::string const &s) : std::invalid_argument{s} {}

        inline explicit Illegal_argument_exception(char const *s) : std::invalid_argument{s} {}
    };

    class Index_out_of_bounds_exception : public std::range_error {
    public:
        explicit Index_out_of_bounds_exception(std::string const &s) : std::range_error{s} {}

        explicit Index_out_of_bounds_exception(char const *s) : std::range_error{s} {}
    };

    class Runtime_exception : public std::runtime_error {
    public:
        explicit Runtime_exception(std::string const &s) : std::runtime_error{s} {}

        explicit Runtime_exception(char const *s) : std::runtime_error{s} {}
    };

    class Unsupported_operation_exception : public std::runtime_error {
    public:
        explicit Unsupported_operation_exception(std::string const &s) : std::runtime_error{s} {}

        explicit Unsupported_operation_exception(char const *s) : std::runtime_error{s} {}
    };

    class Arithmetic_exception : public std::runtime_error {
    public:
        explicit Arithmetic_exception(std::string const &s) : std::runtime_error{s} {}

        explicit Arithmetic_exception(char const *s) : std::runtime_error{s} {}
    };

    class Null_pointer_exception : public std::runtime_error {
    public:
        explicit Null_pointer_exception(std::string const &s) : std::runtime_error{s} {}

        explicit Null_pointer_exception(char const *s) : std::runtime_error{s} {}
    };

    // not portable
    // TODO: prefer reinterpret_cast over union
    union Binary_double {
        double d;
        long l;
    };

    union Binary_float {
        float f;
        int i;
    };

    inline void alg_assert(bool test, char const* msg)
    {
#ifndef NDEBUG
        if (!test) {
            fmt::print(stderr, "%s\n", msg);
            std::abort();
        }
#endif
    }

    class Bad_lexical_cast;

    // Boost/http://www.drdobbs.com/sutters-mill-the-string-formatters-of-ma/184401458
    template<typename Target, typename Source>
    Target lexical_cast(Source arg)
    {
        std::stringstream interpreter;
        auto result = Target{};

        if (!(interpreter << arg) || !(interpreter >> result) || !(interpreter >> std::ws).eof()) {
            throw Bad_lexical_cast{"Unable to perform lexical cast"};
        }

        return result;
    }

    template<typename T>
    T str_to_num(const char *str)
    {
        try {
            return lexical_cast<T>(str);
        }
        catch (const Bad_lexical_cast &e) {
            fmt::print(stderr, "An error occurred while parsing the number: %s, %s\n", str, e.what());
            std::exit(-1);
        }
    }

    template<typename T>
    int safe_read_num()
    {
        char buff[max_num_str_len];
        std::cin.width(max_num_str_len - 1);
        std::cin >> buff;
        return str_to_num<T>(buff);
    }

    template<typename Char_t>
    void split_string(const std::basic_string<Char_t> &str, Char_t c, std::vector<std::basic_string<Char_t>> &v)
    {
        using Str_sz_t = typename std::basic_string<Char_t>::size_type;
        auto j = static_cast<Str_sz_t>(str.find(c));
        auto i = static_cast<Str_sz_t>(0);

        while (j != std::basic_string<Char_t>::npos) {
            v.emplace_back(str.substr(i, j - i));
            i = ++j;
            j = str.find(c, j);

            if (j == std::basic_string<Char_t>::npos) {
                v.emplace_back(str.substr(i, str.size()));
            }
        }
    }

    template<typename Char_t>
    std::vector<std::string> split_string_r(const std::basic_string<Char_t> &str, Char_t c)
    {
        auto v = std::vector<std::basic_string<Char_t>>{};
        split_string(str, c, v);
        return v;
    }

    template<typename Char_t>
    inline std::basic_string<Char_t> pad(
            const std::basic_string<Char_t> &s,
            typename std::basic_string<Char_t>::size_type n,
            Char_t c
    )
    {
        auto t = s;
        if (t.length() < n) {
            t.append(n - t.length(), c);
        }
        return t;
    }

    std::vector<char> str_to_char_vector(std::string const &str);

}

#endif // UTILITY_H
