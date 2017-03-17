#include <sstream>
#include "Std_in.h"

namespace Std_in {
    Position_type __state = 0; // store state
}

bool Std_in::is_empty()
{
    using Traits_type = std::istream::traits_type;
    std::string str;
    std_in >> std::noskipws;
    Traits_type::int_type i;
    Traits_type::char_type ch;
    while (true) {
        i = std_in.get();
        if (i == Traits_type::eof()) {
            break;
        }
        ch = Traits_type::to_char_type(i);
        str += ch;
        if (Traits_type::eq(ch, '\n')) {
            break;
        }
        if (str.size() == str.max_size()) {
            auto err = std_in.rdstate();
            err |= std::ios_base::failbit;
            std_in.setstate(err);
            break;
        }
    }
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        std_in.putback(*it);
    }
    return str.size() <= 1;
}

bool Std_in::has_next_line()
{
    return !is_empty();
}

bool Std_in::has_next_char()
{
    int c = std_in.peek();
    return c != '\0';
}

std::string Std_in::read_line()
{
    std::string line;
    std::getline(std_in, line);
    return line;
}

char Std_in::read_char()
{
    return read_one_of_type<char>();
}

std::string Std_in::read_all()
{
    std::string str;
    while (!is_empty()) {
        str += read_line();
    }
    return str;
}

std::string Std_in::read_string()
{
    return read_line();
}

int Std_in::read_int()
{
    return read_one_of_type<int>();
}

double Std_in::read_double()
{
    return read_one_of_type<double>();
}

float Std_in::read_float()
{
    return read_one_of_type<float>();
}

long Std_in::read_long()
{
    return read_one_of_type<long>();
}

short Std_in::read_short()
{
    return read_one_of_type<short>();
}

char Std_in::read_byte()
{
    return read_one_of_type<char>();
}

bool Std_in::read_boolean()
{
    std::string line;
    std::getline(std_in, line);
    bool tmp;
    std::istringstream(line) >> std::boolalpha >> tmp;
    return tmp;
}

std::vector<std::string> Std_in::read_all_strings()
{
    std::vector<std::string> v;
    std::string line;
    for (; std::getline(std_in, line) && line != "";) {
        v.emplace_back(line);
    }
    return v;
}

std::vector<std::string> Std_in::read_all_lines()
{
    return read_all_strings();
}

std::vector<int> Std_in::read_all_ints()
{
    return read_all_of_type<int>();
}

std::vector<long> Std_in::read_all_longs()
{
    return read_all_of_type<long>();
}

std::vector<double> Std_in::read_all_doubles()
{
    return read_all_of_type<double>();
}

void Std_in::resync()
{
    std_in.sync();
}

void Std_in::_save_state()
{
    Std_in::__state = std_in.tellg();
}

void Std_in::_revert_state()
{
    std_in.seekg(Std_in::__state, std::ios_base::beg);
}