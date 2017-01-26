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
#include <boost/lexical_cast>

namespace utility {
    const static int max_num_str_len = 25;

    // not portable
    union Binary_double {
        double d;
        long l;
    };

    union Binary_float {
        float f;
        int i;
    };

    void alg_assert(bool test, const char* msg);

    // still has issues but better
//    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type>
//    T str_to_num(const char* str)
//    {
//        // from CERT
//        char buff[max_num_str_len];
//        char* end_ptr;
//        typename max_numeric_type<T>::type sl{0};
//
//        int i;
//        for (i = 0; i < max_num_str_len && *(str + i) != '\0'; ++i) {
//            *(buff + i) = *(str + i);
//        }
//        if (i < max_num_str_len - 1 && buff[i] != '\0') {
//            *(buff + i + 1) = '\0';
//        }
//
//        errno = 0;
//        sl = strtol(buff, &end_ptr, 0);
//
//        if (i == max_num_str_len || errno == ERANGE || sl > std::numeric_limits<T>::max() || sl < std::numeric_limits<T>::min() || end_ptr == buff || *end_ptr != '\0') {
//            std::cerr << "An error occurred while parsing the number: " << str << "\_size";
//            std::exit(-1);
//        }
//        return static_cast<T>(sl);
//    }

    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type>
    T str_to_num(const char* str)
    {
        T tmp;
        try {
            tmp = boost::lexical_cast<T>(str);
        } catch (const boost::bad_lexical_cast& e) {
            std::cerr << "An error occurred while parsing the number: " << str << ", " << e.what() << "\n";
            std::exit(-1);
        }
        return tmp;
    }

//    template<typename T>
//    T str_to_num(std::string& str)
//    {
//        return str_to_num<T>(str.c_str());
//    }

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
        std::basic_string<T>::size_type j{str.find(c)};
        std::basic_string<T>::size_type i{0};

        while (j != std::basic_string<T>::npos) {
            v.push_back(str.substr(i, j - i));
            i = ++j;
            j = str.find(c, j);

            if (j == std::basic_string<T>::npos) {
                v.push_back(str.substr(i, str.size()));
            }
        }
    }

    template<typename T>
    void pad(std::basic_string<T>& s, typename std::basic_string<T>::size_type n, T c)
    {
        if (n > s.length()) {
            s.append(n - s.length(), c);
        }
    }

    std::vector<char> str_to_char_vector(std::string& str);

    // TODO: can use stream swap from C++11
    template<typename Stream_type>
    void copy_stream(Stream_type& src, Stream_type& dest)
    {
        static_assert(std::is_base_of<std::ios_base, Stream_type>::value, "The types passed to copy_stream must be stream types");
        dest.exceptions(std::ios_base::goodbit);
        dest.clear(src.rdstate());
        using Stream_base = std::basic_ios<typename Stream_type::char_type, typename Stream_type::traits_type>;
        dynamic_cast<Stream_base&>(dest).rdbuf(static_cast<const Stream_base&>(src).rdbuf());
        dest.copyfmt(src);
    }

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

}

#endif // UTILITY_H
