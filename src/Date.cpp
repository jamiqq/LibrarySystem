#include "Date.h"
#include <ctime>
#include <iostream>

Date::Date()
{
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);

    day = localTime->tm_mday;
    month = localTime->tm_mon + 1;
    year = localTime->tm_year + 1900;
}

Date::Date(int day, int month, int year)
    : day(day), month(month), year(year) {}

Date Date::addDays(int days) const
{
    std::tm date = {};

    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;

    std::mktime(&date);

    date.tm_mday += days;

    std::mktime(&date);

    return Date(
        date.tm_mday,
        date.tm_mon + 1,
        date.tm_year + 1900);
}

void Date::display() const
{
    std::cout << day << "/" << month << "/" << year;
}