#include <sys/socket.h>
#include <ios>
#include "Out.h"

Out::Out(std::ostream& os)
{
    try {
        OutputStreamWriter osw = new OutputStreamWriter(os, CHARSet_NAME);
        out = new PrintWriter(osw, true);
    } catch (IOException e) {
        e.printStackTrace();
    }
}

Out::Out()
{
    this(System.out);
}

Out::Out(Socket& soocket)
{
    try {
        OutputStream os = socket.getOutputStream();
        OutputStreamWriter osw = new OutputStreamWriter(os, CHARSet_NAME);
        out = new PrintWriter(osw, true);
    } catch (IOException e) {
        e.printStackTrace();
    }
}

Out::Out(std::string& filename)
{
    try {
        OutputStream os = new FileOutputStream(filename);
        OutputStreamWriter osw = new OutputStreamWriter(os, CHARSet_NAME);
        out = new PrintWriter(osw, true);
    } catch (IOException e) {
        e.printStackTrace();
    }
}

void Out::close()
{
    out.close();
}

void Out::print_line(bool b)
{
    out << std::boolalpha << b;
}

void Out::print_line(char c)
{

}

void Out::print_line(double d)
{

}

void Out::print_line(float f)
{

}

void Out::print_line(int i)
{

}

void Out::print_line(long l)
{

}

void Out::print_line(short s)
{

}

void Out::print_line()
{

}

void Out::print(bool b)
{

}

void Out::print(char c)
{

}

void Out::print(double d)
{

}

void Out::print(float f)
{

}

void Out::print(int i)
{

}

void Out::print(long l)
{

}

void Out::print(short s)
{

}

void Out::print()
{

}
