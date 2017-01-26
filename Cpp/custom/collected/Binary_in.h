#ifndef BINARY_IN_H
#define BINARY_IN_H

#include <istream>

using Socket = int; // file descriptor for Unix socket
using URL = std::string;

class Binary_in {
public:
    Binary_in();

    Binary_in(std::istream& is);

    // Binary_in(Socket& socket);

    // Binary_in(URL& url);

    Binary_in(std::string& name);

    Binary_in(const char* name);

    static bool exists();

    static bool is_empty();;

    static bool read_boolean();

    static char read_char();

    static char read_char(int r);

    static std::string read_string();

    static short read_short();

    static int read_int();

    static int read_int(int r);

    static long read_long();

    static double read_double();

    static float read_float();

    static char read_byte();

private:
    static const int _eof = EOF;
    static std::istream& _in;
    static int _buffer;
    static int _size;

    static void _fill_buffer();
};

#endif // BINARY_IN_H
