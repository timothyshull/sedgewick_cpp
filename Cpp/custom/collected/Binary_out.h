#ifndef BINARY_OUT_H
#define BINARY_OUT_H

#include <string>

using Socket = int; // Unix file descriptor

class Binary_out {
public:
    Binary_out();

    Binary_out(std::ostream& os);

    Binary_out(std::string& filename);

    Binary_out(const char* filename);

    // Binary_out(Socket& socket);

    static void write_bit(bool x);

    static void write_byte(int x);

    static void flush();

    static void close();

    static void write(bool x);

    static void write(char x);

    static void write(int x);

    static void write(int x, int r);

    static void write(double x);

    static void write(long x);

    static void write(float x);

    static void write(short x);

    static void write(char x, void);

    static void write(char x, int r);

    static void write(std::string& s);

    static void write(std::string& s, int r);

private:
    static std::ostream& _out;
    static int _buffer;
    static int _size;

    static void _write_bit(bool x);

    static void _write_byte(int x);

    static void _clear_buffer();
};

#endif // BINARY_OUT_H
