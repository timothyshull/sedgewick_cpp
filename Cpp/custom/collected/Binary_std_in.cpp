#include "Binary_std_in.h"

void Binary_std_in::close()
{
    try {
        in.close();
    } catch (IOException e) {
        e.printStackTrace();
        throw new RuntimeException("Could not close BinaryStdIn");
    }
}

bool Binary_std_in::isEmpty()
{
    return buffer == EOF
}

bool Binary_std_in::readBoolean()
{
    if (isEmpty()) { throw new RuntimeException("Reading from empty input stream"); }
    n--;
    boolean bit = ((buffer >> n) & 1) == 1;
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
    if (isEmpty()) { throw new RuntimeException("Reading from empty input stream"); }
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
    for (int i = 0; i < r; i++) {
        x <<= 1;
        boolean bit = readBoolean();
        if (bit) { x |= 1; }
    }
    return x;
}

std::string Binary_std_in::readString()
{
    if (isEmpty()) { throw new RuntimeException("Reading from empty input stream"); }

    StringBuilder sb = new StringBuilder();
    while (!isEmpty()) {
        char c = readChar();
        sb.append(c);
    }
    return sb.toString();
}

short Binary_std_in::readShort()
{
    short x = 0;
    for (int i = 0; i < 2; i++) {
        char c = readChar();
        x <<= 8;
        x |= c;
    }
    return x;
}

int Binary_std_in::readInt()
{
    int x = 0;
    for (int i = 0; i < 4; i++) {
        char c = readChar();
        x <<= 8;
        x |= c;
    }
    return x;
}

int Binary_std_in::readInt(int r)
{
    if (r < 1 || r > 32) { throw new IllegalArgumentException("Illegal value of r = " + r); }

    // optimize r = 32 case
    if (r == 32) { return readInt(); }

    int x = 0;
    for (int i = 0; i < r; i++) {
        x <<= 1;
        boolean bit = readBoolean();
        if (bit) { x |= 1; }
    }
    return x;
}

long Binary_std_in::readLong()
{
    long x = 0;
    for (int i = 0; i < 8; i++) {
        char c = readChar();
        x <<= 8;
        x |= c;
    }
    return x;
}

double Binary_std_in::readDouble()
{
    return Double.longBitsToDouble(readLong());
}

float Binary_std_in::readFloat()
{
    return Float.intBitsToFloat(readInt());
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
        System.out.println("EOF");
        buffer = EOF;
        n = -1;
    }
}
