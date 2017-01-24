#ifndef IN_H
#define IN_H

#include <string>
#include <vector>

using Socket = int; // Unix file descriptor
using URL = std::string;

class Scanner;

class In {
public:
    In();

    In(Socket& socket);

    In(URL& url);

    In(std::ifstream& file);

    In(std::string& name, std::true_type);

    In(Scanner& scanner);

    bool exists();

    bool is_empty();

    bool hasNextLine();

    bool hasNextChar();

    std::string read_line();

    char readChar();

    std::string readAll();

    std::string read_string();

    int read_int();

    double read_double();

    float readFloat();

    long readLong();

    short readShort();

    char readByte();

    bool read_boolean();

    std::vector<std::string> readAllStrings();

    std::vector<std::string> readAllLines();

    std::vector<int> readAllInts();

    std::vector<long> readAllLongs();

    std::vector<double> readAllDoubles();

    void close();

    std::vector<int> read_ints(std::string& filename);

    std::vector<double> read_doubles(std::string& filename);

    std::vector<std::string> read_strings(std::string& filename);

    std::vector<int> read_ints();

    std::vector<double> read_doubles();

    std::vector<std::string> read_strings();

};

#endif // IN_H
