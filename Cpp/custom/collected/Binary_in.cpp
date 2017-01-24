#include "Binary_in.h"

Binary_in::Binary_in()
{
    in = new BufferedInputStream(System.in);
    fillBuffer();
}

Binary_in::Binary_in(std::istream& is)
{
    in = new BufferedInputStream(is);
    fillBuffer();
}

Binary_in::Binary_in(Socket& socket)
{
    try {
        InputStream is = socket.getInputStream();
        in = new BufferedInputStream(is);
        fillBuffer();
    } catch (IOException ioe) {
        System.err.print_line("Could not open " + socket);
    }
}

Binary_in::Binary_in(URL& url)
{
    try {
        URLConnection site = url.openConnection();
        InputStream is = site.getInputStream();
        in = new BufferedInputStream(is);
        fillBuffer();
    } catch (IOException ioe) {
        System.err.print_line("Could not open " + url);
    }
}

Binary_in::Binary_in(std::string& name, std::true_type)
{
    try {
        // first try to read file from local file system
        File file = new File(name);
        if (file.exists()) {
            FileInputStream fis = new FileInputStream(file);
            in = new BufferedInputStream(fis);
            fillBuffer();
            return;
        }

        // next try for files included in jar
        URL url = getClass().getResource(name);

        // or URL from web
        if (url == null) {
            url = new URL(name);
        }

        URLConnection site = url.openConnection();
        InputStream is = site.getInputStream();
        in = new BufferedInputStream(is);
        fillBuffer();
    } catch (IOException ioe) {
        System.err.print_line("Could not open " + name);
    }
}

bool Binary_in::exists()
{
    return in != null;
}

bool Binary_in::is_empty()
{
    return buffer == _EOF;
}

bool Binary_in::read_boolean()
{
    if (is_empty()) { throw utility::Runtime_exception("Reading from empty input stream"); }
    n--;
    bool bit = ((buffer >> n) & 1) == 1;
    if (n == 0) { fillBuffer(); }
    return bit;
}

char Binary_in::readChar()
{
    if (n == 8) {
        int x = buffer;
        fillBuffer();
        return (char) (x & 0xff);
    }

    // combine last N bits of current buffer with first 8-N bits of new buffer
    int x = buffer;
    x <<= (8 - n);
    int oldN = n;
    fillBuffer();
    if (is_empty()) { throw utility::Runtime_exception("Reading from empty input stream"); }
    n = oldN;
    x |= (buffer >> > n);
    return (char) (x & 0xff);
}

char Binary_in::readChar(int r)
{
    if (r < 1 || r > 16) { throw utility::Runtime_exception("Illegal value of r = " + r); }

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

std::string Binary_in::read_string()
{
    if (is_empty()) { throw utility::Runtime_exception("Reading from empty input stream"); }

    std::stringstream sb = new std::stringstream();
    while (!is_empty()) {
        char c = readChar();
        sb.append(c);
    }
    return sb.to_string();
}

short Binary_in::readShort()
{
    short x = 0;
    for (int i = 0; i < 2; ++i) {
        char c = readChar();
        x <<= 8;
        x |= c;
    }
    return x;
}

int Binary_in::read_int()
{
    int x = 0;
    for (int i = 0; i < 4; ++i) {
        char c = readChar();
        x <<= 8;
        x |= c;
    }
    return x;
}

int Binary_in::read_int(int r)
{
    if (r < 1 || r > 32) { throw utility::Runtime_exception("Illegal value of r = " + r); }

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

long Binary_in::readLong()
{
    long x = 0;
    for (int i = 0; i < 8; ++i) {
        char c = readChar();
        x <<= 8;
        x |= c;
    }
    return x;
}

double Binary_in::read_double()
{
    return Double.longBitsToDouble(readLong());
}

float Binary_in::readFloat()
{
    return Float.intBitsToFloat(read_int());
}

char Binary_in::readByte()
{
    char c = readChar();
    byte x = (byte)(c & 0xff);
    return x;
}

void Binary_in::fillBuffer()
{
    try {
        buffer = in.read();
        n = 8;
    } catch (IOException e) {
        System.err.print_line("EOF");
        buffer = EOF;
        n = -1;
    }
}
