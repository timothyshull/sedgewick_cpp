#ifndef DATE_H
#define DATE_H

#include <vector>
#include <string>

class Date {
public:
    Date(int month, int day, int year);

    Date(std::string& date);

    inline int month() const noexcept { return _month; }

    inline int day() const noexcept { return _day; }

    inline int year() const noexcept { return _year; }

    Date next() const;

    inline bool is_after(const Date& rhs) const noexcept { return rhs < *this; }

    inline bool is_before(const Date& rhs) const noexcept { return *this < rhs; }

    inline std::string to_string() const { return "Date(" + std::to_string(_month) + "/" + std::to_string(_day) + "/" + std::to_string(_year); }

    bool operator<(const Date& rhs) const;

    inline bool Date::operator==(const Date& rhs) const { return (_month == rhs._month) && (_day == rhs._day) && (_year == rhs._year); }

    int hash_code() const;

private:
    const static std::vector<int> _days{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int _month;
    const int _day;
    const int _year;

    Date(std::vector<std::string>&& date);

    bool _is_valid(int m, int d, int y) const;

    bool _is_leap_year(int y) const;
};

#endif // DATE_H
