#include <string>
#include <iostream>
#include "In.h"

int main(int argc, char* argv[])
{
    In in;
    std::string url_name{"http://introcs.cs.princeton.edu/stdlib/InTest.txt"};

    std::cout << "readAll() from URL " << url_name;
    std::cout << "---------------------------------------------------------------------------";
    try {
        in = In{url_name};
        std::cout << in.readAll();
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    std::cout << "\n";

    std::cout << "read_line() from URL " + url_name;
    std::cout << "---------------------------------------------------------------------------";
    try {
        in = In{url_name};
        while (!in.is_empty()) {
            std::string s = in.read_line();
            std::cout << s;
        }
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    std::cout << "\n";

    std::cout << "read_string() from URL " + url_name;
    std::cout << "---------------------------------------------------------------------------";
    try {
        in = In{url_name};
        while (!in.is_empty()) {
            std::string s = in.read_string();
            std::cout << s;
        }
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    std::cout << "\n";

    std::cout << "read_line() from current directory");
    std::cout << "---------------------------------------------------------------------------");
    try {
        in = In{"./InTest.txt"};
        while (!in.is_empty()) {
            std::string s = in.read_line();
            std::cout << s;
        }
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    std::cout << "\n";

    std::cout << "read_line() from relative path");
    std::cout << "---------------------------------------------------------------------------");
    try {
        in = In{"../stdlib/InTest.txt"};
        while (!in.is_empty()) {
            std::string s = in.read_line();
            std::cout << s;
        }
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    std::cout << "\n";

    std::cout << "read_char() from file");
    std::cout << "---------------------------------------------------------------------------");
    try {
        in = In{"InTest.txt"};
        while (!in.is_empty()) {
            char c = in.read_char();
            std::cout << c;
        }
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    std::cout << "\n";
    std::cout << "\n";

    std::cout << "read_line() from absolute OS X / Linux path");
    std::cout << "---------------------------------------------------------------------------");
    in = new In("/_size/fs/introcs/www/java/stdlib/InTest.txt");
    try {
        while (!in.is_empty()) {
            std::string s = in.read_line();
            std::cout << s;
        }
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    std::cout << "\n";

    std::cout << "read_line() from absolute Windows path");
    std::cout << "---------------------------------------------------------------------------");
    try {
        in = In{"G:\\www\\introcs\\stdlib\\InTest.txt"};
        while (!in.is_empty()) {
            std::string s = in.read_line();
            std::cout << s;
        }
        std::cout << "\n";
    } catch (std::exception& e) {
        std::cerr << e.what();
    }
    std::cout << "\n";
    return 0;
}
