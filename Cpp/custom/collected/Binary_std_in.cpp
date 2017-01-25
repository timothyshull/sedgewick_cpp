#include "Binary_std_in.h"
#include "utility.h"

void Binary_std_in::close()
{
    try {
        _in.close();
    } catch (IOException e) {
        e.printStackTrace();
        throw utility::Runtime_exception("Could not close BinaryStdIn");
    }
}

bool Binary_std_in::is_empty()
{
    return _buffer == _eof;
}

bool Binary_std_in::read_boolean()
{
    if (is_empty()) { throw utility::Runtime_exception("Reading from empty input stream"); }
    _size--;
    bool bit = ((_buffer >> _size) & 1) == 1;
    if (_size == 0) { _fill_buffer(); }
    return bit;
}

char Binary_std_in::read_char()
{
    if (_size == 8) {
        int x = _buffer;
        _fill_buffer();
        return (char) (x & 0xff);
    }

    // combine last _size bits of current _buffer with first 8-_size bits of new _buffer
    int x = _buffer;
    x <<= (8 - _size);
    int oldN = _size;
    _fill_buffer();
    if (is_empty()) { throw utility::Runtime_exception("Reading from empty input stream"); }
    _size = oldN;
    x |= (_buffer >> _size);
    return (char) (x & 0xff);
}

char Binary_std_in::read_char(int r)
{
    if (r < 1 || r > 16) { throw utility::Illegal_argument_exception("Illegal value of r = " + r); }

    // optimize r = 8 case
    if (r == 8) { return read_char(); }

    char x = 0;
    for (int i{0}; i < r; ++i) {
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
        char c = read_char();
        sb.append(c);
    }
    return sb.to_string();
}

short Binary_std_in::read_short()
{
    short x = 0;
    for (int i{0}; i < 2; ++i) {
        char c = read_char();
        x <<= 8;
        x |= c;
    }
    return x;
}

int Binary_std_in::read_int()
{
    int x = 0;
    for (int i{0}; i < 4; ++i) {
        char c = read_char();
        x <<= 8;
        x |= c;
    }
    return x;
}

int Binary_std_in::read_int(int r)
{
    if (r < 1 || r > 32) { throw utility::Illegal_argument_exception("Illegal value of r = " + r); }

    // optimize r = 32 case
    if (r == 32) { return read_int(); }

    int x = 0;
    for (int i{0}; i < r; ++i) {
        x <<= 1;
        bool bit = read_boolean();
        if (bit) { x |= 1; }
    }
    return x;
}

long Binary_std_in::read_long()
{
    long x = 0;
    for (int i{0}; i < 8; ++i) {
        char c = read_char();
        x <<= 8;
        x |= c;
    }
    return x;
}

double Binary_std_in::read_double()
{
    return Double.longBitsToDouble(read_long());
}

float Binary_std_in::read_float()
{
    return Float.intBitsToFloat(read_int());
}

char Binary_std_in::read_byte()
{
    char c = read_char();
    byte x = (byte)(c & 0xff);
    return x;
}

void Binary_std_in::_fill_buffer()
{
    try {
        _buffer = _in.read();
        _size = 8;
    } catch (IOException e) {
        System.out.print_line("_eof");
        _buffer = _eof;
        _size = -1;
    }
}
