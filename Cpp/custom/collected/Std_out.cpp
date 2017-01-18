#include "Std_out.h"

namespace Std_out {
    void close() {}

    void print_line(bool b)
    {
        std_out << std::boolalpha << b << "\n";
    }

    void print_line(char c)
    {
        std_out << c << "\n";
    }

    void print_line(double d)
    {
        std_out << d << "\n";
    }

    void print_line(float f)
    {
        std_out << f << "\n";
    }

    void print_line(int i)
    {
        std_out << i << "\n";
    }

    void print_line(long l)
    {
        std_out << l << "\n";
    }

    void print_line(short s)
    {
        std_out << s << "\n";
    }

    void print_line()
    {
        std_out << "\n";
    }

    void print(bool b)
    {
        std_out << std::boolalpha << b;
        std_out.flush();
    }

    void print(char c)
    {
        std_out << c;
        std_out.flush();
    }

    void print(double d)
    {
        std_out << d;
        std_out.flush();
    }

    void print(float f)
    {
        std_out << f;
        std_out.flush();
    }

    void print(int i)
    {
        std_out << i;
        std_out.flush();
    }

    void print(long l)
    {
        std_out << l;
        std_out.flush();
    }

    void print(short s)
    {
        std_out << s;
        std_out.flush();
    }

    void print()
    {
        std_out.flush();
    }

}