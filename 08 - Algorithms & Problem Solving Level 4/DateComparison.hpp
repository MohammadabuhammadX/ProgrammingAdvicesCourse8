// DateComparison.hpp
#pragma once
#include "DateLib.hpp"

struct sDate {
    int Year;
    int Month;
    int Day;
};

namespace DateComparison {

    bool IsDate1BeforeDate2(const sDate& d1, const sDate& d2) {
        if (d1.Year != d2.Year) return d1.Year < d2.Year;
        if (d1.Month != d2.Month) return d1.Month < d2.Month;
        return d1.Day < d2.Day;
    }

    bool IsDateEqual(const sDate& d1, const sDate& d2) {
        return d1.Year == d2.Year && d1.Month == d2.Month && d1.Day == d2.Day;
    }

    int GetDifferenceInDays(sDate d1, sDate d2, bool includeEndDay = false) {
        if (IsDateEqual(d1, d2)) return includeEndDay ? 1 : 0;

        if (IsDate1BeforeDate2(d2, d1)) {
            // Swap so d1 <= d2
            sDate temp = d1; d1 = d2; d2 = temp;
        }

        int count = 0;
        while (IsDate1BeforeDate2(d1, d2)) {
            count++;
            // Increment d1
            d1.Day++;
            if (d1.Day > DateLib::NumberOfDaysInMonth(d1.Month, d1.Year)) {
                d1.Day = 1;
                d1.Month++;
                if (d1.Month > 12) {
                    d1.Month = 1;
                    d1.Year++;
                }
            }
        }

        return includeEndDay ? count + 1 : count;
    }
}