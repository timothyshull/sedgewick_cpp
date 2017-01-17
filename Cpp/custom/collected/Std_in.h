#ifndef STD_IN_H
#define STD_IN_H

#include <string>
#include <locale>
#include <regex>
#include <vector>
#include <iostream>
#include <sstream>

namespace Std_in {
    const static std::string charset_name = std::string("UTF-8");

    const static std::locale locale = std::locale("en_US");

    static std::istream& std_in = std::cin;

    using Position_type = typename std::istream::traits_type::pos_type;

    bool is_empty();

    bool has_next_line();

    bool has_next_char();

    template<typename T>
    T read_one_of_type() {
        // ss.imbue(Std_in::locale);
        std::string line;
        std::getline(std_in, line);
        T tmp;
        std::istringstream(line) >> tmp;
        return tmp;
    }

    template<typename T>
    std::vector<T> read_all_of_type() {
        // ss.imbue(Std_in::locale);
        std::vector<T> v;
        std::string line;
        T tmp;
        for (; std::getline(std_in, line) && line != "";) {
            std::istringstream(line) >> tmp;
            v.emplace_back(tmp);
        }
        return v;
    }

    std::string read_line();

    char read_char();

    std::string read_all();

    std::string read_string();

    int read_int();

    double read_double();

    float read_float();

    long read_long();

    short read_short();

    // gsl::byte read_byte();
    char read_byte();

    bool read_boolean();

    std::vector<std::string> read_all_strings();

    std::vector<std::string> read_all_lines();

    std::vector<int> read_all_ints();

    std::vector<long> read_all_longs();

    std::vector<double> read_all_doubles();

    void resync();

    // void set_scanner(Scanner& scanner);
    void _save_state();

    void _revert_state();

};

#endif //STD_IN_H
