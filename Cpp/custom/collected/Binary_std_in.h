#ifndef BINARY_STD_IN_H
#define BINARY_STD_IN_H

#include <istream>

class Binary_std_in {
public:
    void close();

    bool is_empty();

    bool read_boolean();

    char read_char();

    char read_char(int r);

    std::string read_string();

    short read_short();

    int read_int();

    int read_int(int r);

    long read_long();

    double read_double();

    float read_float();

    char read_byte();

private:
    const static int _eof = -1;
    std::istream&& _in;
    int _buffer;
    int _size;

    void _fill_buffer();
};

#endif // BINARY_STD_IN_H
