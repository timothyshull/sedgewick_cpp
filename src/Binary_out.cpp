#include <iostream>
#include "Binary_out.h"
#include "utility.h"

Binary_out::Binary_out() : _out{std::cout} {}

Binary_out::Binary_out(std::ostream& os) : _out{os} {}

Binary_out::Binary_out(std::string& filename) : _out{filename} {}

Binary_out::Binary_out(const char* filename) : _out{filename} {}

// Binary_out::Binary_out(Socket& socket)

void Binary_out::write_bit(bool x)
{
    _buffer <<= 1;
    if (x) { _buffer |= 1; }

    _size++;
    if (_size == 8) { _clear_buffer(); }
}

void Binary_out::write_byte(int x)
{
    utility::alg_assert(x >= 0 && x < 256, "Binary_out value check failed");

    if (_size == 0) {
        try {
            _out << x;
        } catch (std::exception& e) {
            std::cerr << e.what();
        }
        return;
    }

    bool bit;
    for (int i = 0; i < 8; ++i) {
        bit = ((x >> (8 - i - 1)) & 1) == 1;
        write_bit(bit);
    }
}

void Binary_out::flush()
{
    _clear_buffer();
    try {
        _out.flush();
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
}

void Binary_out::close()
{
    flush();
    try {
        _out.clear(); // no ostream close
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
}

void Binary_out::write(bool x)
{
    write_bit(x);
}

void Binary_out::write(char x)
{
    write_byte(x & 0xff);
}

void Binary_out::write(int x)
{
    write_byte((x >> 24) & 0xff);
    write_byte((x >> 16) & 0xff);
    write_byte((x >> 8) & 0xff);
    write_byte((x >> 0) & 0xff);
}

void Binary_out::write(int x, int r)
{
    if (r == 32) {
        write(x);
        return;
    }
    if (r < 1 || r > 32) { throw utility::Illegal_argument_exception("Illegal value for r = " + std::to_string(r)); }
    if (x >= (1 << r)) { throw utility::Illegal_argument_exception("Illegal " + std::to_string(r) + "-bit char = " + std::to_string(x)); }
    for (auto i = 0; i < r; ++i) {
        bool bit = ((x >> (r - i - 1)) & 1) == 1;
        write_bit(bit);
    }
}

void Binary_out::write(double x)
{
    utility::Binary_double bd;
    bd.d = x;
    write(bd.l);
}

void Binary_out::write(long x)
{
    write_byte((int) ((x >> 56) & 0xff));
    write_byte((int) ((x >> 48) & 0xff));
    write_byte((int) ((x >> 40) & 0xff));
    write_byte((int) ((x >> 32) & 0xff));
    write_byte((int) ((x >> 24) & 0xff));
    write_byte((int) ((x >> 16) & 0xff));
    write_byte((int) ((x >> 8) & 0xff));
    write_byte((int) ((x >> 0) & 0xff));
}

void Binary_out::write(float x)
{
    utility::Binary_float bf;
    bf.f = x;
    write(bf.i);
}

void Binary_out::write(short x)
{
    write_byte((x >> 8) & 0xff);
    write_byte((x >> 0) & 0xff);
}

void Binary_out::write(char x, void)
{
    if (x < 0 || x >= 256) { throw utility::Illegal_argument_exception("Illegal 8-bit char = " + x); }
    write_byte(x);
}

void Binary_out::write(char x, int r)
{
    if (r == 8) {
        write(x);
        return;
    }
    if (r < 1 || r > 16) { throw utility::Illegal_argument_exception("Illegal value for r = " + std::to_string(r)); }
    if (x >= (1 << r)) { throw utility::Illegal_argument_exception("Illegal " + std::to_string(r) + "-bit char = " + std::to_string(x)); }
    for (auto i = 0; i < r; ++i) {
        bool bit = ((x >> (r - i - 1)) & 1) == 1;
        write_bit(bit);
    }
}

void Binary_out::write(std::string& s)
{
    for (auto i = 0; i < s.length(); ++i) {
        write(s[i]);
    }
}

void Binary_out::write(std::string& s, int r)
{
    for (auto i = 0; i < s.length(); ++i) {
        write(s[i], r);
    }
}

void Binary_out::_write_bit(bool x)
{
    _buffer <<= 1;
    if (x) { _buffer |= 1; }

    ++_size;
    if (_size == 8) { _clear_buffer(); }
}

void Binary_out::_write_byte(int x)
{
    utility::alg_assert(x >= 0 && x < 256, "Binary_out _write_byte int value check failed");

    if (_size == 0) {
        try {
            _out << x;
        } catch (std::exception& e) {
            std::cerr << e.what();
        }
        return;
    }

    for (auto i = 0; i < 8; ++i) {
        bool bit = ((x >> (8 - i - 1)) & 1) == 1;
        write_bit(bit);
    }
}

void Binary_out::_clear_buffer()
{
    if (_size == 0) { return; }
    if (_size > 0) { _buffer <<= (8 - _size); }
    try {
        _out << _buffer;
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    _size = 0;
    _buffer = 0;
}
