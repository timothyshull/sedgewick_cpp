#include "Date.h"
#include "utility.h"

Date::Date(int month, int day, int year) : _month{month}, _day{day}, _year{year}
{
    if (!_is_valid(month, day, year)) { throw utility::Illegal_argument_exception{"Invalid date"}; }
}

Date::Date(std::string& date) : Date{utility::split_string_r(date, '/')} {}

Date::Date(std::vector<std::string>&& date)
        : _month{utility::str_to_num<int>(date[0].c_str())},
          _day{utility::str_to_num<int>(date[1].c_str())},
          _year{utility::str_to_num<int>(date[2].c_str())}
{
    if (date.size() != 3) {
        throw utility::Illegal_argument_exception{"Invalid date"};
    }
    if (!_is_valid(_month, _day, _year)) { throw utility::Illegal_argument_exception{"Invalid date"}; }
}

Date Date::next() const
{
    if (_is_valid(_month, _day + 1, _year)) {
        return Date(_month, _day + 1, _year);
    } else if (_is_valid(_month + 1, 1, _year)) {
        return Date(_month + 1, 1, _year);
    } else {
        return Date(1, 1, _year + 1);
    }
}

bool Date::operator<(const Date& rhs) const
{
    if (_year < rhs._year) { return true; }
    if (_year > rhs._year) { return false; }
    if (_month < rhs._month) { return true; }
    if (_month > rhs._month) { return false; }
    return _day < rhs._day;
}

int Date::hash_code() const
{
    auto hash = 17;
    hash = 31 * hash + _month;
    hash = 31 * hash + _day;
    hash = 31 * hash + _year;
    return hash;
}

bool Date::_is_valid(int m, int d, int y) const
{
    if (m < 1 || m > 12) { return false; }
    if (d < 1 || d > _days[m]) { return false; }
    if (m == 2 && d == 29 && !_is_leap_year(y)) { return false; }
    return true;
}

bool Date::_is_leap_year(int y) const
{
    if (y % 400 == 0) { return true; }
    if (y % 100 == 0) { return false; }
    return y % 4 == 0;
}
