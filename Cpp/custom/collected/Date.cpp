#include "Date.h"

Date::Date(int month, int day, int year)
{
    if (!isValid(month, day, year)) throw new IllegalArgumentException("Invalid date");
    this.month = month;
    this.day = day;
    this.year = year;
}

Date::Date(std::string& date)
{
    String[] fields = date.split("/");
    if (fields.length != 3) {
        throw new IllegalArgumentException("Invalid date");
    }
    month = Integer.parseInt(fields[0]);
    day = Integer.parseInt(fields[1]);
    year = Integer.parseInt(fields[2]);
    if (!isValid(month, day, year)) throw new IllegalArgumentException("Invalid date");
}

int Date::month()
{
    return month;
}

int Date::day()
{
    return day;
}

int Date::year()
{
    return year;
}

Date Date::next()
{
    if (isValid(month, day + 1, year)) return new Date(month, day + 1, year);
    else if (isValid(month + 1, 1, year)) return new Date(month + 1, 1, year);
    else return new Date(1, 1, year + 1);
}

bool Date::is_after(Date& that)
{
    return compareTo(that) > 0;
}

bool Date::isBefore(Date& that)
{
    return compareTo(that) < 0;
}

std::string Date::to_string()
{
    return month + "/" + day + "/" + year;
}

bool Date::operator<(Date& rhs)
{
    if (this.year < that.year) return -1;
    if (this.year > that.year) return +1;
    if (this.month < that.month) return -1;
    if (this.month > that.month) return +1;
    if (this.day < that.day) return -1;
    if (this.day > that.day) return +1;
    return 0;
}

bool Date::operator=(Date& rhs)
{
    if (other == this) return true;
    if (other == null) return false;
    if (other.getClass() != this.getClass()) return false;
    Date that = (Date) other;
    return (this.month == that.month) && (this.day == that.day) && (this.year == that.year);
}

int Date::hashCode()
{
    int hash = 17;
    hash = 31 * hash + month;
    hash = 31 * hash + day;
    hash = 31 * hash + year;
    return hash;
}

bool Date::isValid(int m, int d, int y)
{
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > DAYS[m]) return false;
    if (m == 2 && d == 29 && !isLeapYear(y)) return false;
    return true;
}

bool Date::isLeapYear(int y)
{
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return y % 4 == 0;
}
