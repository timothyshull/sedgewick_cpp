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

    bool isEmpty();

    bool hasNextLine();

    bool hasNextChar();

    std::string readLine();

    char readChar();

    std::string readAll();

    std::string readString();

    int readInt();

    double readDouble();

    float readFloat();

    long readLong();

    short readShort();

    char readByte();

    bool readBoolean();

    std::vector<std::string> readAllStrings();

    std::vector<std::string> readAllLines();

    std::vector<int> readAllInts();

    std::vector<long> readAllLongs();

    std::vector<double> readAllDoubles();

    void close();

    std::vector<int> readInts(std::string& filename);

    std::vector<double> readDoubles(std::string& filename);

    std::vector<std::string> readStrings(std::string& filename);

    std::vector<int> readInts();

    std::vector<double> readDoubles();

    std::vector<std::string> readStrings();

};

#endif // IN_H
