#include "Binary_std_in.h"

void Binary_std_in::close()
{
    try {
        in.close();
    } catch (IOException e) {
        e.printStackTrace();
        throw utility::Runtime_exception("Could not close BinaryStdIn");
    }
}

bool Binary_std_in::is_empty()
{
    return buffer == EOF
}

bool Binary_std_in::read_boolean()
{
    if (is_empty()) { throw utility::Runtime_exception("Reading from empty input stream"); }
    n--;
    bool bit = ((buffer >> n) & 1) == 1;
    if (n == 0) { fillBuffer(); }
    return bit;
}

char Binary_std_in::readChar()
{
    if (n == 8) {
        int x = buffer;
        fillBuffer();
        return (char) (x & 0xff);
    }

    // combine last n bits of current buffer with first 8-n bits of new buffer
    int x = buffer;
    x <<= (8 - n);
    int oldN = n;
    fillBuffer();
    if (is_empty()) { throw utility::Runtime_exception("Reading from empty input stream"); }
    n = oldN;
    x |= (buffer >> > n);
    return (char) (x & 0xff);
}

char Binary_std_in::readChar(int r)
{
    if (r < 1 || r > 16) { throw new IllegalArgumentException("Illegal value of r = " + r); }

    // optimize r = 8 case
    if (r == 8) { return readChar(); }

    char x = 0;
    for (int i = 0; i < r; ++i) {
        x <<= 1;
        bool bit = read_boolean();
        if (bit) { x |= 1; }
    }
    return x;
}

std::string Binary_std_in::read_string()
{
    if (is_empty()) { throw utility::Runtime_exception("Reading from empty input stream"); }

    std::stringstream sb = new std::stringstream();
    while (!is_empty()) {
        char c = readChar();
        sb.append(c);
    }
    return sb.to_string();
}

short Binary_std_in::readShort()
{
    short x = 0;
    for (int i = 0; i < 2; ++i) {
        char c = readChar();
        x <<= 8;
        x |= c;
    }
    return x;
}

int Binary_std_in::read_int()
{
    int x = 0;
    for (int i = 0; i < 4; ++i) {
        char c = readChar();
        x <<= 8;
        x |= c;
    }
    return x;
}

int Binary_std_in::read_int(int r)
{
    if (r < 1 || r > 32) { throw new IllegalArgumentException("Illegal value of r = " + r); }

    // optimize r = 32 case
    if (r == 32) { return read_int(); }

    int x = 0;
    for (int i = 0; i < r; ++i) {
        x <<= 1;
        bool bit = read_boolean();
        if (bit) { x |= 1; }
    }
    return x;
}

long Binary_std_in::readLong()
{
    long x = 0;
    for (int i = 0; i < 8; ++i) {
        char c = readChar();
        x <<= 8;
        x |= c;
    }
    return x;
}

double Binary_std_in::read_double()
{
    return Double.longBitsToDouble(readLong());
}

float Binary_std_in::readFloat()
{
    return Float.intBitsToFloat(read_int());
}

char Binary_std_in::readByte()
{
    char c = readChar();
    byte x = (byte)(c & 0xff);
    return x;
}

void Binary_std_in::fillBuffer()
{
    try {
        buffer = in.read();
        n = 8;
    } catch (IOException e) {
        System.out.print_line("EOF");
        buffer = EOF;
        n = -1;
    }
}
