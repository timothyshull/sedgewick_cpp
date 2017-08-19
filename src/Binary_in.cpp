#include <iostream>
#include <sstream>

#include "Binary_in.h"
#include "utility.h"

Binary_in::Binary_in() : _in{std::cin}
{
    _fill_buffer();
}

Binary_in::Binary_in(std::istream& is) : _in{is}
{
    _fill_buffer();
}

// TODO: implement with boost::iostreams
//Binary_in::Binary_in(Socket& socket)

// TODO: implement with boost::asio::ip::tcp::iostream
//Binary_in::Binary_in(URL& url) : _in{boost::asio::ip::tcp::istream {url}}

// leaves error handling to istream
Binary_in::Binary_in(std::string& name) : _in{name} {}

Binary_in::Binary_in(const char* name) : _in{name} {}

bool Binary_in::exists()
{
    return !_in.good();
}

bool Binary_in::is_empty()
{
    return _buffer == _eof;
}

bool Binary_in::read_boolean()
{
    if (is_empty()) { throw utility::Runtime_exception{"Reading from empty input stream"}; }
    _size--;
    bool bit = ((_buffer >> _size) & 1) == 1;
    if (_size == 0) { _fill_buffer(); }
    return bit;
}

char Binary_in::read_char()
{
    if (_size == 8) {
        int x = _buffer;
        _fill_buffer();
        return (char) (x & 0xff);
    }

    // combine last N bits of current _buffer with first 8-N bits of new _buffer
    int x = _buffer;
    x <<= (8 - _size);
    int oldN = _size;
    _fill_buffer();
    if (is_empty()) { throw utility::Runtime_exception{"Reading from empty input stream"}; }
    _size = oldN;
    x |= (_buffer >> _size);
    return (char) (x & 0xff);
}

char Binary_in::read_char(int r)
{
    if (r < 1 || r > 16) { throw utility::Runtime_exception{"Illegal value of r = " + r}; }

    if (r == 8) { return read_char(); }

    char x = 0;
    for (auto i = 0; i < r; ++i) {
        x <<= 1;
        bool bit = read_boolean();
        if (bit) { x |= 1; }
    }
    return x;
}

std::string Binary_in::read_string()
{
    if (is_empty()) { throw utility::Runtime_exception{"Reading from empty input stream"}; }

    std::stringstream ss;
    while (!is_empty()) {
        char c = read_char();
        ss << c;
    }
    return ss.str();
}

short Binary_in::read_short()
{
    short x = 0;
    for (auto i = 0; i < 2; ++i) {
        char c = read_char();
        x <<= 8;
        x |= c;
    }
    return x;
}

int Binary_in::read_int()
{
    int x = 0;
    for (auto i = 0; i < 4; ++i) {
        char c = read_char();
        x <<= 8;
        x |= c;
    }
    return x;
}

int Binary_in::read_int(int r)
{
    if (r < 1 || r > 32) { throw utility::Runtime_exception{"Illegal value of r = " + r}; }
    if (r == 32) { return read_int(); }

    int x = 0;
    for (auto i = 0; i < r; ++i) {
        x <<= 1;
        bool bit = read_boolean();
        if (bit) { x |= 1; }
    }
    return x;
}

long Binary_in::read_long()
{
    long x = 0;
    for (auto i = 0; i < 8; ++i) {
        char c = read_char();
        x <<= 8;
        x |= c;
    }
    return x;
}

double Binary_in::read_double()
{
    long l{read_long()};
    utility::Binary_double bd;
    bd.l = l;
    return bd.d;
}

float Binary_in::read_float()
{
    auto i = read_int();
    utility::Binary_float bf;
    bf.i = i;
    return bf.f;
}

char Binary_in::read_byte()
{
    return read_char();
}

void Binary_in::_fill_buffer()
{
    try {
        _buffer = _in.get();
        _size = 8;
    } catch (std::exception& e) {
        std::cerr << "EOF " << e.what() << "\n";
        _buffer = _eof;
        _size = -1;
    }
}
