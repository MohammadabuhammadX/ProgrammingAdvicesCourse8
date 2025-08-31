// SystemDate.hpp
#pragma once
#include <ctime>
#include "sDate.h"  // We'll define this separately

sDate GetSystemDate() {
    time_t t = time(0);
    tm* now = localtime(&t);

    sDate date;
    date.Year = now->tm_year + 1900;
    date.Month = now->tm_mon + 1;
    date.Day = now->tm_mday;

    return date;
}