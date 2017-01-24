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

namespace utility {
    void assert(bool test, const char msg[]);

    // TODO: add handling for selecting strtoll, stroul, and strtoull based
    // on template type
    int safe_read_integer()
    {
        // from CERT
        char buff[25];
        char* end_ptr;
        long sl{0};
        int si{0};
        int exit{0};

        std::cin.width(24);
        std::cin >> buff;

        errno = 0;

        sl = strtol(buff, &end_ptr, 0);

        if (ERANGE == errno) {
            exit = -1;
            std::cerr << "number out of range\n";
        } else if (sl > INT_MAX) {
            exit = -1;
            std::cerr << sl << " too large!\n";
        } else if (sl < INT_MIN) {
            exit = -1;
            std::cerr << sl << " too small!\n";
        } else if (end_ptr == buff) {
            exit = -1;
            std::cerr << "not valid numeric input\n";
        } else if (*end_ptr != '\0') {
            exit = -1;
            std::cerr << "extra characters on input line\n";
        } else {
            si = static_cast<int>(sl);
        }

        if (exit != 0) {
            std::exit(exit);
        } else {
            return si;
        }
    }

    int safe_convert_integer(const char * str)
    {
        // from CERT
        const int buff_size = 25;
        char buff[buff_size];
        char* end_ptr;
        long sl{0};
        int si{0};
        int exit{0};

        int i;
        for (i = 0; i < buff_size && *(str + i) != '\0'; ++i) {
            *(buff + i) = *(str + i);
            if (i == buff_size) {
                exit = -1;
            }
        }
        if (i < buff_size - 1 && buff[i] != '\0') {
            *(buff + i + 1) = '\0';
        }

        errno = 0;
        sl = strtol(buff, &end_ptr, 0);

        if (exit == -1) {
            std::cerr << "The length of the input string was too large\n";
        } else if (ERANGE == errno) {
            exit = -1;
            std::cerr << "The number was out of range\n";
        } else if (sl > INT_MAX) {
            exit = -1;
            std::cerr << sl << " is too large\n";
        } else if (sl < INT_MIN) {
            exit = -1;
            std::cerr << sl << " is too small\n";
        } else if (end_ptr == buff) {
            exit = -1;
            std::cerr << "is not valid numeric input\n";
        } else if (*end_ptr != '\0') {
            exit = -1;
            std::cerr << "Extra characters were included in the input line\n";
        } else {
            si = static_cast<int>(sl);
        }

        if (exit != 0) {
            std::exit(exit);
        } else {
            return si;
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

#if _LIBCPP_STD_VER < 14

    template<class T>
    struct __unique_if {
        using __unique_single = std::unique_ptr<T>;
    };

    template<class T>
    struct __unique_if<T[]> {
        using __unique_array_unknown_bound = std::unique_ptr<T[]>;
    };

    template<class T, std::size_t num_ptrs>
    struct __unique_if<T[num_ptrs]> {
        typedef void __unique_array_known_bound;
    };

    template<class T, class... Args>
    inline
    typename __unique_if<T>::__unique_single
    make_unique(Args&& ... argv)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(argv)...));
    }

    template<class T>
    inline
    typename __unique_if<T>::__unique_array_unknown_bound
    make_unique(size_t n)
    {
        using Unique_ptr = typename std::remove_extent<T>::type;
        return std::unique_ptr<T>(new Unique_ptr[n]());
    }

    template<class T, class... Args>
    typename __unique_if<T>::__unique_array_known_bound
    make_unique(Args&& ...) = delete;

#else

    template<class T, class... Args>
    using make_unique<T, Args...> = std::make_unique<T, Args...>;

    template<class T>
    using make_unique<T> = std::make_unique<T>;

#endif  // _LIBCPP_STD_VER < 14
}

#endif // UTILITY_H
