#ifndef UTILITY_H
#define UTILITY_H

#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <memory>
#include <string>
#include <ios>
#include <type_traits>
#include <iostream>
#include <vector>
#include <sstream>

namespace utility {
    const static int max_num_str_len = 25;

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

    void alg_assert(bool test, const char* msg);

    class bad_lexical_cast : public std::exception {};

    // Boost/http://www.drdobbs.com/sutters-mill-the-string-formatters-of-ma/184401458
    template<typename Target, typename Source>
    Target lexical_cast(Source arg)
    {
        std::stringstream interpreter;
        Target result;

        if (!(interpreter << arg) || !(interpreter >> result) || !(interpreter >> std::ws).eof()) {
            throw bad_lexical_cast{};
        }

        return result;
    }

    template<typename T>
    T str_to_num(const char* str)
    {
        T tmp;
        try {
            tmp = lexical_cast<T>(str);
        } catch (const bad_lexical_cast& e) {
            std::cerr << "An error occurred while parsing the number: " << str << ", " << e.what() << "\n";
            std::exit(-1);
        }
        return tmp;
    }

    template<typename T>
    int safe_read_num()
    {
        char buff[max_num_str_len];
        std::cin.width(max_num_str_len - 1);
        std::cin >> buff;
        return str_to_num<T>(buff);
    }

    template<typename T>
    void split_string(const std::basic_string<T>& str, T c, std::vector<std::basic_string<T>>& v)
    {
        typename std::basic_string<T>::size_type j{str.find(c)};
        typename std::basic_string<T>::size_type i{0};

        while (j != std::basic_string<T>::npos) {
            v.emplace_back(str.substr(i, j - i));
            i = ++j;
            j = str.find(c, j);

            if (j == std::basic_string<T>::npos) {
                v.emplace_back(str.substr(i, str.size()));
            }
        }
    }

    template<typename T>
    std::vector<std::string> split_string_r(const std::basic_string<T>& str, T c)
    {
        std::vector<std::basic_string<T>> v;
        typename std::basic_string<T>::size_type j{str.find(c)};
        typename std::basic_string<T>::size_type i{0};

        while (j != std::basic_string<T>::npos) {
            v.emplace_back(str.substr(i, j - i));
            i = ++j;
            j = str.find(c, j);

            if (j == std::basic_string<T>::npos) {
                v.emplace_back(str.substr(i, str.size()));
            }
        }
        return v;
    }

    template<typename T>
    inline void pad(std::basic_string<T>& s, typename std::basic_string<T>::size_type n, T c) { if (n > s.length()) { s.append(n - s.length(), c); }}

    std::vector<char> str_to_char_vector(std::string& str);

    class No_such_element_exception : public std::range_error {
    public:
        inline explicit No_such_element_exception(const std::string& s) : std::range_error{s} {}

        inline explicit No_such_element_exception(const char* s) : std::range_error{s} {}

        virtual ~No_such_element_exception() noexcept {};
    };

    class Illegal_argument_exception : public std::invalid_argument {
    public:
        inline explicit Illegal_argument_exception(const std::string& s) : std::invalid_argument{s} {}

        inline explicit Illegal_argument_exception(const char* s) : std::invalid_argument{s} {}

        virtual ~Illegal_argument_exception() noexcept {};
    };

    class Index_out_of_bounds_exception : public std::range_error {
    public:
        inline explicit Index_out_of_bounds_exception(const std::string& s) : std::range_error{s} {}

        inline explicit Index_out_of_bounds_exception(const char* s) : std::range_error{s} {}

        virtual ~Index_out_of_bounds_exception() noexcept {};
    };

    class Runtime_exception : public std::runtime_error {
    public:
        inline explicit Runtime_exception(const std::string& s) : std::runtime_error{s} {}

        inline explicit Runtime_exception(const char* s) : std::runtime_error{s} {}

        virtual ~Runtime_exception() noexcept {};
    };

    class Unsupported_operation_exception : public std::runtime_error {
    public:
        inline explicit Unsupported_operation_exception(const std::string& s) : std::runtime_error{s} {}

        inline explicit Unsupported_operation_exception(const char* s) : std::runtime_error{s} {}

        virtual ~Unsupported_operation_exception() noexcept {};
    };

    class Arithmetic_exception : public std::runtime_error {
    public:
        inline explicit Arithmetic_exception(const std::string& s) : std::runtime_error{s} {}

        inline explicit Arithmetic_exception(const char* s) : std::runtime_error{s} {}

        virtual ~Arithmetic_exception() noexcept {};
    };

    class Null_pointer_exception : public std::runtime_error {
    public:
        inline explicit Null_pointer_exception(const std::string& s) : std::runtime_error{s} {}

        inline explicit Null_pointer_exception(const char* s) : std::runtime_error{s} {}

        virtual ~Null_pointer_exception() noexcept {};
    };

}

#endif // UTILITY_H
