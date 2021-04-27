#ifndef DATETIME_H
#define DATETIME_H

#include <cstdint>
#include <ctime>
#include <string>

namespace goodok {

    struct Time {
        Time() : hours(0), minutes(0), seconds(0) {}
        Time(int s, int m, int h) :
                hours(h),
                minutes(m),
                seconds(s) {}

        int hours;
        int minutes;
        int seconds;

        Time &operator=(const std::tm &tm);

        friend bool operator==(const Time &lhs, const Time &rhs);
        friend bool operator<(const Time &lhs, const Time &rhs);
    };

    struct Date {
        Date() : day(0), month(0), year(0) {}
        Date(int d, int m, int y) :
                day(d),
                month(m),
                year(y) {}

        int day;
        int month;
        int year;

        Date &operator=(const std::tm &tm);

        friend bool operator==(const Date &lhs, const Date &rhs);
        friend bool operator<(const Date &lhs, const Date &rhs);
    };

    struct DateTime {
        DateTime() = default;
        DateTime(Time const& a_time, Date const& a_date) : time(a_time), date(a_date) {}

        Time time;
        Date date;

        DateTime &operator=(std::tm const& tm);

        friend bool operator==(DateTime const& lhs, DateTime const& rhs);
        friend bool operator<(DateTime const& lhs, DateTime const& rhs);
    };

}
#endif // DATETIME_H
