#ifndef OUT_H
#define OUT_H

#include <iosfwd>
#include <cstdio>
#include <vector>

using Socket = int;


class Out {
public:
    Out(std::ostream& os);
    Out();
    Out(Socket& soocket);
    Out(std::string& filename);
    void close();
    template<typename... Args>
    void printf(const char* format, const Args& ... args)
    {
        int sz = std::snprintf(nullptr, 0, format, args...);
        std::vector<char> buf(sz + 1);
        std::snprintf(&buf[0], buf.size(), format, args...);
        out << std::string(buf.begin(), buf.end() - 1) << "\n";
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
        out << t;
        out << "\n";
    }

    template<typename T>
    void print_line(T&& t)
    {
        out << t;
        out << "\n";
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
        out << t;
    }

    template<typename T>
    void print(T&& t)
    {
        out << t << "\n";
    }

    void print();
private:
    std::ostream& out;
};

#endif // OUT_H
