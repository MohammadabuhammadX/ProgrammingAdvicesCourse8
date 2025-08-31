// CalendarLib.hpp
#pragma once
#include <iostream>
#include <iomanip>
#include "DateLib.hpp"

namespace CalendarLib {

    std::string GetDayName(int dayIndex) {
        std::string names[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        if (dayIndex < 0 || dayIndex > 6) return "??";
        return names[dayIndex];
    }

    std::string GetMonthName(int month) {
        std::string names[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                               "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
        if (month < 1 || month > 12) return "Invalid";
        return names[month - 1];
    }

    // Zeller's Congruence (simplified for Gregorian calendar)
    int GetDayOfWeek(int day, int month, int year) {
        if (month < 3) {
            month += 12;
            year--;
        }
        int q = day;
        int m = month;
        int k = year % 100;
        int j = year / 100;
        int h = (q + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
        return (h + 6) % 7; // Convert to 0=Sun, 1=Mon, ..., 6=Sat
    }

    void PrintDayNames() {
        std::string days[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        for (int i = 0; i < 7; ++i)
            std::cout << std::setw(4) << days[i];
        std::cout << "\n";
    }

    void PrintMonth(int year, int month) {
        std::cout << "\n\n";
        std::cout << "         " << GetMonthName(month) << " " << year << "\n";
        PrintDayNames();

        int startDay = GetDayOfWeek(1, month, year);
        int days = DateLib::NumberOfDaysInMonth(month, year);

        for (int i = 0; i < startDay; ++i)
            std::cout << std::setw(4) << " ";

        for (int day = 1; day <= days; ++day) {
            std::cout << std::setw(4) << day;
            if ((startDay + day) % 7 == 0)
                std::cout << "\n";
        }
        std::cout << "\n";
    }

    void PrintYear(int year) {
        std::cout << "\n==================================\n";
        std::cout << "          Calendar - " << year << "\n";
        std::cout << "==================================\n\n";

        for (int m = 1; m <= 12; ++m)
            PrintMonth(year, m);
    }
}