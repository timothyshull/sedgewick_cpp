#ifndef BINARY_STD_IN_H
#define BINARY_STD_IN_H

#include <istream>

class Binary_std_in {
public:
    void close();

    bool is_empty();

    bool read_boolean();

    char readChar();

    char readChar(int r);

    std::string read_string();

    short readShort();

    int read_int();

    int read_int(int r);

    long readLong();

    double read_double();

    float readFloat();

    char readByte();

private:
    const static int _EOF = 1;
    std::istream&& in;
    int buffer;
    int n;

    void fillBuffer();
};

#endif // BINARY_STD_IN_H
