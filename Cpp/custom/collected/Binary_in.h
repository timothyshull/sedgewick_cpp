#ifndef BINARY_IN_H
#define BINARY_IN_H

#include <istream>

using Socket = int; // file descriptor for Unix socket
using URL = std::string;

class Binary_in {
public:
    Binary_in();
    Binary_in(std::istream& is);
    Binary_in(Socket& socket);
    Binary_in(URL& url);
    Binary_in(std::string& name, std::true_type); // just for overload
    bool exists();
    bool is_empty();;
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
    const static int _EOF = -1;
    std::istream& in;
    int buffer;
    int n;

void fillBuffer();
};

#endif // BINARY_IN_H
