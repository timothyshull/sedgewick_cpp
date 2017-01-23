#ifndef BINARY_OUT_H
#define BINARY_OUT_H

#include <string>

using Socket = int; // Unix file descriptor

class Binary_out {
public:
    Binary_out();

    Binary_out(std::ostream& os);

    Binary_out(std::string filename);

    Binary_out(Socket& socket);

    void writeBit(bool x);

    void writeByte(int x);

    void flush();

    void close();

    void write(bool x);

    void write(char x);

    void write(int x);

    void write(int x, int r);

    void write(double x);

    void write(long x);

    void write(float x);

    void write(short x);

    void write(char x, std::true_type);

    void write(char x, int r);

    void write(std::string& s);

    void write(std::string& s, int r);

private:
    std::ostream& out;
    int buffer;
    int n;

    void writeBit(bool x, std::false_type);

    void writeByte(int x, std::false_type);

    void clearBuffer();
};

#endif // BINARY_OUT_H
