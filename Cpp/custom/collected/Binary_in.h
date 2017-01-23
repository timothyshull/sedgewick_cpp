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
    bool isEmpty();;
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
    const static int _EOF = -1;
    std::istream& in;
    int buffer;
    int n;

void fillBuffer();
};

#endif // BINARY_IN_H
