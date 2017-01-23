#ifndef BINARY_STD_IN_H
#define BINARY_STD_IN_H

#include <istream>

class Binary_std_in {
public:
    void close();

    bool isEmpty();

    bool readBoolean();

    char readChar();

    char readChar(int r);

    std::string readString();

    short readShort();

    int readInt();

    int readInt(int r);

    long readLong();

    double readDouble();

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
