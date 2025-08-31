
#pragma once
#include <string>

namespace DateLib {

    bool IsLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int NumberOfDaysInMonth(int month, int year) {
        if (month < 1 || month > 12) return 0;

        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (month == 2 && IsLeapYear(year))
            return 29;
        return days[month - 1];
    }

    int DaysInYear(int year) {
        return IsLeapYear(year) ? 366 : 365;
    }

    int HoursInYear(int year) { return DaysInYear(year) * 24; }
    int MinutesInYear(int year) { return HoursInYear(year) * 60; }
    int SecondsInYear(int year) { return MinutesInYear(year) * 60; }

    int TotalDaysFromStartOfYear(int day, int month, int year) {
        int total = 0;
        for (int m = 1; m < month; ++m) {
            total += NumberOfDaysInMonth(m, year);
        }
        return total + day;
    }
}