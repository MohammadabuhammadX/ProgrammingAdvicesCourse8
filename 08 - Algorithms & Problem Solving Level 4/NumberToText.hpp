#pragma once
#include <string>

namespace NumberToText {
    std::string Convert(int Number) {
        if (Number == 0) {
            return "Zero";
        }

        if (Number >= 1 && Number <= 19) {
            std::string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
                                  "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                                  "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
            return arr[Number];
        }

        if (Number >= 20 && Number <= 99) {
            std::string tens[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty",
                                   "Seventy", "Eighty", "Ninety" };
            return tens[Number / 10] + ((Number % 10 != 0) ? " " + Convert(Number % 10) : "");
        }

        if (Number >= 100 && Number <= 999) {
            return Convert(Number / 100) + " Hundred" + ((Number % 100 != 0) ? " " + Convert(Number % 100) : "");
        }

        if (Number >= 1000 && Number <= 999999) {
            return Convert(Number / 1000) + " Thousand" + ((Number % 1000 != 0) ? " " + Convert(Number % 1000) : "");
        }

        if (Number >= 1000000 && Number <= 999999999) {
            return Convert(Number / 1000000) + " Million" + ((Number % 1000000 != 0) ? " " + Convert(Number % 1000000) : "");
        }

        if (Number >= 1000000000) {
            return Convert(Number / 1000000000) + " Billion" + ((Number % 1000000000 != 0) ? " " + Convert(Number % 1000000000) : "");
        }

        return "Out of range";
    }
}