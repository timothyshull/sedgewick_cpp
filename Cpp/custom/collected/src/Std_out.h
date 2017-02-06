#ifndef STD_OUT_H
#define STD_OUT_H

#include <ostream>
#include <vector>
#include <iostream>

namespace Std_out {
    static std::ostream& std_out = std::cout;

    void close();

    template<typename... Args>
    void printf(const char* format, const Args& ... argv)
    {
        int sz = std::snprintf(nullptr, 0, format, argv...);
        std::vector<char> buf(sz + 1);
        std::snprintf(&buf[0], buf.size(), format, argv...);
        std::cout << std::string(buf.begin(), buf.end() - 1) << "\n";
    }

    // these should be template specializations
    void print_line(bool b);

    void print_line(char c);

    void print_line(double d);

    void print_line(float f);

    void print_line(int i);

    void print_line(long l);

    void print_line(short s);

    template<typename T>
    void print_line(const T& t)
    {
        std_out << t;
        std_out << "\n";
    }

    template<typename T>
    void print_line(T&& t)
    {
        std_out << t;
        std_out << "\n";
    }

    void print_line();

    void print(bool b);

    void print(char c);

    void print(double d);

    void print(float f);

    void print(int i);

    void print(long l);

    void print(short s);

    template<typename T>
    void print(const T& t)
    {
        std_out << t;
    }

    template<typename T>
    void print(T&& t)
    {
        std_out << t;
    }

    void print();

};

#endif // STD_OUT_H
