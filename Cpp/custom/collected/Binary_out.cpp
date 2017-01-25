#include "Binary_out.h"

Binary_out::Binary_out()
{
    out = new BufferedOutputStream(System.out);
}

Binary_out::Binary_out(std::ostream& os)
{
    out = new BufferedOutputStream(os);
}

Binary_out::Binary_out(std::string filename)
{
    try {
        OutputStream os = new FileOutputStream(filename);
        out = new BufferedOutputStream(os);
    } catch (IOException e) {
        e.printStackTrace();
    }
}

Binary_out::Binary_out(Socket& socket)
{
    try {
        OutputStream os = socket.getOutputStream();
        out = new BufferedOutputStream(os);
    } catch (IOException e) {
        e.printStackTrace();
    }
}

void Binary_out::writeBit(bool x)
{

}

void Binary_out::writeByte(int x)
{

}

void Binary_out::flush()
{
    clearBuffer();
    try {
        out.flush();
    } catch (IOException e) {
        e.printStackTrace();
    }
}

void Binary_out::close()
{
    flush();
    try {
        out.close();
    } catch (IOException e) {
        e.printStackTrace();
    }
}

void Binary_out::write(bool x)
{
    writeBit(x);
}

void Binary_out::write(char x)
{
    writeByte(x & 0xff);
}

void Binary_out::write(int x)
{
    writeByte((x >> 24) & 0xff);
    writeByte((x >> 16) & 0xff);
    writeByte((x >> 8) & 0xff);
    writeByte((x >> 0) & 0xff);
}

void Binary_out::write(int x, int r)
{
    if (r == 32) {
        write(x);
        return;
    }
    if (r < 1 || r > 32) { throw utility::Illegal_argument_exception("Illegal value for r = " + r); }
    if (x >= (1 << r)) { throw utility::Illegal_argument_exception("Illegal " + r + "-bit char = " + x); }
    for (int i = 0; i < r; ++i) {
        bool bit = ((x >> (r - i - 1)) & 1) == 1;
        writeBit(bit);
    }
}

void Binary_out::write(double x)
{
    write(Double.doubleToRawLongBits(x));
}

void Binary_out::write(long x)
{
    writeByte((int) ((x >> 56) & 0xff));
    writeByte((int) ((x >> 48) & 0xff));
    writeByte((int) ((x >> 40) & 0xff));
    writeByte((int) ((x >> 32) & 0xff));
    writeByte((int) ((x >> 24) & 0xff));
    writeByte((int) ((x >> 16) & 0xff));
    writeByte((int) ((x >> 8) & 0xff));
    writeByte((int) ((x >> 0) & 0xff));
}

void Binary_out::write(float x)
{
    write(Float.floatToRawIntBits(x));
}

void Binary_out::write(short x)
{
    writeByte((x >> 8) & 0xff);
    writeByte((x >> 0) & 0xff);
}

void Binary_out::write(char x, std::true_type)
{
    if (x < 0 || x >= 256) { throw utility::Illegal_argument_exception("Illegal 8-bit char = " + x); }
    writeByte(x);
}

void Binary_out::write(char x, int r)
{
    if (r == 8) {
        write(x);
        return;
    }
    if (r < 1 || r > 16) { throw utility::Illegal_argument_exception("Illegal value for r = " + r); }
    if (x >= (1 << r)) { throw utility::Illegal_argument_exception("Illegal " + r + "-bit char = " + x); }
    for (int i = 0; i < r; ++i) {
        bool bit = ((x >> > (r - i - 1)) & 1) == 1;
        writeBit(bit);
    }
}

void Binary_out::write(std::string& s)
{
    for (int i = 0; i < s.length(); ++i) {
        write(s.charAt(i));
    }
}

void Binary_out::write(std::string& s, int r)
{
    for (int i = 0; i < s.length(); ++i) {
        write(s.charAt(i), r);
    }
}

void Binary_out::writeBit(bool x, std::false_type)
{
    buffer <<= 1;
    if (x) { buffer |= 1; }

    // if _buffer is full (8 bits), write out as a single byte
    ++n;
    if (n == 8) { clearBuffer(); }
}

void Binary_out::writeByte(int x, std::false_type)
{
    assert
    x >= 0 && x < 256;

    // optimized if byte-aligned
    if (n == 0) {
        try {
            out.write(x);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return;
    }

    // otherwise write one bit at a time
    for (int i = 0; i < 8; ++i) {
        bool bit = ((x >> > (8 - i - 1)) & 1) == 1;
        writeBit(bit);
    }
}

void Binary_out::clearBuffer()
{
    if (n == 0) { return; }
    if (n > 0) { buffer <<= (8 - n); }
    try {
        out.write(buffer);
    } catch (IOException e) {
        e.printStackTrace();
    }
    n = 0;
    buffer = 0;
}
