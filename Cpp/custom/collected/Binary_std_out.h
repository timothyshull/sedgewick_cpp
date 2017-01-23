#ifndef BINARY_STD_OUT_H
#define BINARY_STD_OUT_H

#include <ostream>

class Binary_std_out {
public:
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
    void write(char x);
    void write(char x, int r);
    void write(std::string& s);
    void write(std::string& s, int r);


private:
    std::ostream& out;
    int buffer;
    int n;

    void writeBit(bool bit);
    void writeByte(int x);
    void clearBuffer();
};

#endif // BINARY_STD_OUT_H
