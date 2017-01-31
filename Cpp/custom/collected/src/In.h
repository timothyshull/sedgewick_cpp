#ifndef IN_H
#define IN_H

#include <string>
#include <vector>
// #include <boost/variant.hpp>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/filesystem.hpp>

#include "utility.h"

using Socket = boost::asio::local::stream_protocol::socket;
using Socket_endpoint = boost::asio::local::stream_protocol::endpoint;
using Async_iostream = boost::asio::ip::tcp::iostream;

// default to assuming ifstream
template<typename T>
class In {
public:
    In() = delete;

    ~In() = default;

    inline In(std::ifstream& input_file) { std::swap(_input, input_file); };

    In(std::string& name)
    {
        if (!boost::filesystem::exists(name)) {
            throw utility::Illegal_argument_exception{"The file " + name + " does not exist"};
        }
        _input = std::ifstream{name};
    }

    In(std::string&& name) : In{name} {}

    In(const char* name) : In{std::string{name}} {}

    inline bool exists() const { return _input.is_open(); };

    bool is_empty()
    {
        using Traits_type = std::ifstream::traits_type;
        std::string str;
        _input >> std::noskipws;
        Traits_type::int_type i;
        Traits_type::char_type ch;
        while (true) {
            i = _input.get(); // sentry setup and EOF handled _in get, no need to handle again here
            if (i == Traits_type::eof()) {
                break;
            }
            ch = Traits_type::to_char_type(i);
            str += ch;
            if (Traits_type::eq(ch, '\n')) {
                break;
            }
            if (str.size() == str.max_size()) {
                auto err = _input.rdstate();
                err |= std::ios_base::failbit;
                _input.setstate(err);
                break;
            }
        }
        for (auto it = str.rbegin(); it != str.rend(); ++it) {
            _input.putback(*it);
        }
        return str.size() <= 1;
    }

    template<typename To_read>
    To_read read_one_of_type()
    {
        // ss.imbue(Std_in::locale);
        std::string line;
        std::getline(_input, line);
        To_read tmp;
        std::istringstream(line) >> tmp;
        return tmp;
    }

    template<typename To_read>
    std::vector<To_read> read_all_of_type()
    {
        // ss.imbue(Std_in::locale);
        std::vector<To_read> v;
        std::string line;
        To_read tmp;
        for (; std::getline(_input, line) && line != "";) {
            std::istringstream(line) >> tmp;
            v.emplace_back(tmp);
        }
        return v;
    }

    inline bool has_next_line() { return !is_empty(); };

    bool has_next_char()
    {

        using Traits_type = std::ifstream::traits_type;
        int c{_input.peek()};
        return c != '\0' && c != Traits_type::eof();
    }

    std::string read_line()
    {
        std::string line;
        std::getline(_input, line);
        return line;
    }

    // TODO: fix this in Std_in
    inline char read_char() { return _input.get(); }

    std::string read_all()
    {
        std::string str;
        while (!is_empty()) {
            str += read_line();
        }
        return str;
    }

    inline std::string read_string() { return read_line(); }

    inline int read_int() { return read_one_of_type<int>(); }

    inline double read_double() { return read_one_of_type<double>(); }

    inline float read_float() { return read_one_of_type<float>(); }

    inline long read_long() { return read_one_of_type<long>(); }

    inline short read_short() { return read_one_of_type<short>(); }

    inline char read_byte() { return read_one_of_type<char>(); }

    bool read_boolean()
    {
        std::string line;
        std::getline(_input, line);
        bool tmp;
        std::istringstream(line) >> std::boolalpha >> tmp;
        return tmp;
    }

    std::vector<std::string> read_all_strings()
    {
        std::vector<std::string> v;
        std::string line;
        for (; std::getline(_input, line) && line != "";) {
            v.emplace_back(line);
        }
        return v;
    }

    inline std::vector<std::string> read_all_lines() { return read_all_strings(); }

    inline std::vector<int> read_all_ints() { return read_all_of_type<int>(); }

    inline std::vector<long> read_all_longs() { return read_all_of_type<long>(); }

    inline std::vector<double> read_all_doubles() { return read_all_of_type<double>(); }

    inline void resync() { _input.sync(); }

    inline void close() { _input.close(); }

private:
    T _input;
};

template<>
class In<Async_iostream> {
public:
    In();

    In(std::string& url)
            : _input{}
    {
        try {
            boost::asio::io_service io_service;

            boost::asio::steady_timer timer{io_service, std::chrono::seconds{60}};
            timer.async_wait([](const boost::system::error_code& ec) { std::cout << "3 sec\n"; });
            // ioservice.run();
            boost::asio::ip::tcp::resolver resolver{io_service};
            boost::asio::ip::tcp::resolver::query query{url, "http"};
            boost::asio::ip::tcp::resolver::iterator iter{resolver.resolve(query)};
            boost::asio::ip::tcp::resolver::iterator end;

            if (iter == end) {
                throw utility::Illegal_argument_exception{"The URL " + url + " is not resolvable"};
            }

            _input.expires_from_now(boost::posix_time::seconds(60));
            _input.connect(url, "http");
            _input << "GET /LICENSE_1_0.txt HTTP/1.0\r\n";
            _input << "Host: www.boost.org\r\n";
            _input << "Accept: */*\r\n";
            _input << "Connection: close\r\n\r\n";
            _input.flush();
            _ss << _input.rdbuf();
        } catch (...) { // boost::system::system_error
            throw utility::Illegal_argument_exception{"The URL " + url + " is not resolvable"};
        }
    }

    In(std::string&& url) : In{url} {}

    In(const char* url) : In{std::string{url}} {}

    inline bool exists() { return _ss.good(); }

    inline bool is_empty()
    {
        using Traits_type = std::stringstream::traits_type;
        std::string str;
        _ss >> std::noskipws;
        Traits_type::int_type i;
        Traits_type::char_type ch;
        while (true) {
            i = _ss.get(); // sentry setup and EOF handled _in get, no need to handle again here
            if (i == Traits_type::eof()) {
                break;
            }
            ch = Traits_type::to_char_type(i);
            str += ch;
            if (Traits_type::eq(ch, '\n')) {
                break;
            }
            if (str.size() == str.max_size()) {
                auto err = _ss.rdstate();
                err |= std::ios_base::failbit;
                _ss.setstate(err);
                break;
            }
        }
        for (auto it = str.rbegin(); it != str.rend(); ++it) {
            _ss.putback(*it);
        }
        return str.size() <= 1;
    };

    template<typename To_read>
    To_read read_one_of_type()
    {
        // ss.imbue(Std_in::locale);
        std::string line;
        std::getline(_ss, line);
        To_read tmp;
        std::istringstream(line) >> tmp;
        return tmp;
    }

    template<typename To_read>
    std::vector<To_read> read_all_of_type()
    {
        // ss.imbue(Std_in::locale);
        std::vector<To_read> v;
        std::string line;
        To_read tmp;
        for (; std::getline(_ss, line) && line != "";) {
            std::istringstream(line) >> tmp;
            v.emplace_back(tmp);
        }
        return v;
    }

    inline bool has_next_line() { return !is_empty(); };

    bool has_next_char()
    {

        using Traits_type = std::ifstream::traits_type;
        int c{_ss.peek()};
        return c != '\0' && c != Traits_type::eof();
    };

    std::string read_line()
    {
        std::string line;
        std::getline(_ss, line);
        return line;
    };

    // TODO: fix this in Std_in
    inline char read_char() { return _ss.get(); }

    std::string read_all()
    {
        std::string str;
        while (!is_empty()) {
            str += read_line();
        }
        return str;
    }

    inline std::string read_string() { return read_line(); }

    inline int read_int() { return read_one_of_type<int>(); }

    inline double read_double() { return read_one_of_type<double>(); }

    inline float read_float() { return read_one_of_type<float>(); }

    inline long read_long() { return read_one_of_type<long>(); }

    inline short read_short() { return read_one_of_type<short>(); }

    inline char read_byte() { return read_one_of_type<char>(); }

    bool read_boolean()
    {
        std::string line;
        std::getline(_ss, line);
        bool tmp;
        std::istringstream(line) >> std::boolalpha >> tmp;
        return tmp;
    }

    std::vector<std::string> read_all_strings()
    {
        std::vector<std::string> v;
        std::string line;
        for (; std::getline(_ss, line) && line != "";) {
            v.emplace_back(line);
        }
        return v;
    }

    inline std::vector<std::string> read_all_lines() { return read_all_strings(); }

    inline std::vector<int> read_all_ints() { return read_all_of_type<int>(); }

    inline std::vector<long> read_all_longs() { return read_all_of_type<long>(); }

    inline std::vector<double> read_all_doubles() { return read_all_of_type<double>(); }

    inline void resync() { _ss.sync(); }

    void close()
    {
        try {
            _input.close();
        } catch (...) {}
        _ss.clear();
    }

private:
    Async_iostream _input;
    std::stringstream _ss;
};



//template<typename T>
//class In : public In_base<std::is_same<T, Socket>::value> {
//public:
//    In();
//
//    In(Socket& socket);
//
//    In(std::ifstream& file);
//
//    In(std::string& name, bool is_url)
//    {
//        if (!is_url && !boost::filesystem::exists(name)) {
//            throw utility::Illegal_argument_exception{"The file " + name + " does not exist"};
//        }
//
//        if (!is_url) {
//            std::ifstream input_file{name};
//            _input = Variant_type{std::ifstream{name}};
//        } else {
//            ip::tcp::iostream stream;
//        }
//    };
//
//    bool exists();
//
//    bool is_empty();
//
//    bool has_next_line();
//
//    bool has_next_char();
//
//    std::string read_line();
//
//    char read_char();
//
//    std::string read_all();
//
//    std::string read_string();
//
//    int read_int();
//
//    double read_double();
//
//    float read_float();
//
//    long read_long();
//
//    short read_short();
//
//    char read_byte();
//
//    bool read_boolean();
//
//    std::vector<std::string> read_all_strings();
//
//    std::vector<std::string> read_all_lines();
//
//    std::vector<int> read_all_ints();
//
//    std::vector<long> read_all_longs();
//
//    std::vector<double> read_all_doubles();
//
//    void close();
//
//    std::vector<int> read_ints(std::string& filename);
//
//    std::vector<double> read_doubles(std::string& filename);
//
//    std::vector<std::string> read_strings(std::string& filename);
//
//    std::vector<int> read_ints();
//
//    std::vector<double> read_doubles();
//
//    std::vector<std::string> read_strings();
//
//private:
//    T _input;
//    In_type _in_type;
//
//    template<typename>
//    friend class In_base;
//};

namespace In_tests {
    void test1(std::string&& filename);

    void test2(std::string&& filename);

    void test3(std::string&& filename);

    void test4(std::string&& filename);

    void test5(std::string&& filename);

    void test6(std::string&& filename);

    void test7(std::string&& filename);

    void test8(std::string&& filename);
}

#endif // IN_H


//local::stream_protocol::endpoint ep("/tmp/foobar");
//local::stream_protocol::socket socket(my_io_service);
//socket.connect(ep);



//ip::tcp::iostream stream;
//stream.expires_from_now(boost::posix_time::seconds(60));
//stream.connect("www.boost.org", "http");
//stream << "GET /LICENSE_1_0.txt HTTP/1.0\r\n";
//stream << "Host: www.boost.org\r\n";
//stream << "Accept: */*\r\n";
//stream << "Connection: close\r\n\r\n";
//stream.flush();
//std::cout << stream.rdbuf();