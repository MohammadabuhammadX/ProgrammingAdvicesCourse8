#include <iostream>
#include <iomanip>
using namespace std;

int ReadNumber(string message) {
	int Number;
	cout << message;
	cin >> Number;
	return Number;
}

struct sDate
{
	int Year;
	int Month;
	int Day;
};

bool IsLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int NumberOfDaysInMonth(int month, int year) {
	if (month < 1 || month > 12)
		return 0;

	int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	if (month == 2)
		return IsLeapYear(year) ? 29 : 28;
	return arrDays[month - 1];
}

int PrintTotalDaysFromTheBeginningOfYear(int year, int month, int day) {

	int TotalDays = 0;

	for (int i = 1; i <= month - 1; i++)
	{
		TotalDays += NumberOfDaysInMonth(i, year);
	}
	TotalDays += day;
	return TotalDays;

}

bool IsLastDayInMonth(int day, int month, int year) {

	if (NumberOfDaysInMonth(month, year) == day)
		return true;
	return false;

}

bool IsLastMonthInYear(int month) {

	if (month == 12)
		return true;
	return false;
}

sDate ReadFullDate() {
	sDate Date;

	Date.Day = ReadNumber("\nPlease enter a Day : ");
	Date.Month = ReadNumber("\nPlease enter a Month : ");
	Date.Year = ReadNumber("\nPlease enter a Year : ");

	return Date;
}

int main() {
	int day = ReadNumber("Please enter a Day : ");
	int month = ReadNumber("Please enter a Month : ");
	int year = ReadNumber("Please enter a Year : ");

	if (IsLastDayInMonth(day, month, year)) {

		cout << "\nYes , Day is last day in month. ";
	}
	else
	{
		cout << "\nNo , Day isn't last day in month. ";

	}

	if (IsLastMonthInYear(month)) {

		cout << "\nYes, Month is last Month in year";
	}
	else
	{
		cout << "\nNo, Month isn't last Month in year";

	}

	return 0;
}

namespace problems {
	class Problem1 {
		string NumberToText(int Number) {
			if (Number == 0) {
				return "";
			}

			if (Number >= 1 && Number <= 19) {
				string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
								 "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
								 "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
				return arr[Number] + string(" ");
			}

			if (Number >= 20 && Number <= 99) {
				string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty",
								 "Seventy", "Eighty", "Ninety" };
				return arr[Number / 10] + string(" ") + NumberToText(Number % 10);
			}

			if (Number >= 100 && Number <= 199) {
				return "One Hundred " + NumberToText(Number % 100);
			}

			if (Number >= 200 && Number <= 999) {
				return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
			}

			if (Number >= 1000 && Number <= 1999) {
				return "One Thousand " + NumberToText(Number % 1000);
			}

			if (Number >= 2000 && Number <= 999999) {
				return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
			}

			if (Number >= 1000000 && Number <= 1999999) {
				return "One Million " + NumberToText(Number % 1000000);
			}

			if (Number >= 2000000 && Number <= 999999999) {
				return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
			}

			if (Number >= 1000000000 && Number <= 1999999999) {
				return "One Billion " + NumberToText(Number % 1000000000);
			}
			else {
				return NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
			}
		}

		int ReadNumber() {
			int Number;
			cout << "\nEnter a Number? ";
			cin >> Number;
			return Number;
		}

		int main() {
			int Number = ReadNumber();
			cout << NumberToText(Number);
			system("pause>0");
			return 0;
		}
	};
	class Problem2 {
		int ReadNumber() {
			int Number;
			cout << "\nEnter a Number? ";
			cin >> Number;
			return Number;
		}

		bool IsLeapYear(int year) {

			if (year % 400 == 0) {
				return true;
			}
			else if (year % 100 == 0)
			{
				return false;
			}
			else if (year % 4 == 0)
			{
				return true;
			}
			else
			{
				return false;
			}

		}

		int main() {

			int Number = ReadNumber();

			if (!IsLeapYear(Number)) {
				cout << "It is not a leap year";
			}
			else {
				cout << "It is a leap year";
			}

			return 0;
		};

	};
	class Problem3 {
		int ReadNumber() {
			int Number;
			cout << "\nEnter a Number? ";
			cin >> Number;
			return Number;
		}

		bool IsLeapYear(int year) {

			//return (year % 400 == 0) ? true :(year % 100 == 0) ? false : (year % 4 == 0) ? true : false;
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}


		int main() {

			int Number = ReadNumber();

			if (!IsLeapYear(Number)) {
				cout << "It is not a leap year";
			}
			else {
				cout << "It is a leap year";
			}

			return 0;
		}
	};
	class Problem4MyCode {
		/* static int YearToDays = 366;
		 static int YearToDaysLeapYear = 365;
		 static int DaysToHours = YearToDays * 24;
		 static int DaysToHoursLeapYear = YearToDaysLeapYear * 24;
		 static int HoursToMinutes = DaysToHours * 60;
		 static int HoursToMinutesLeapYear = DaysToHoursLeapYear * 60;
		 static int MinutesToSecons = HoursToMinutes * 60;
		 static int MinutesToSeconsLeapYear = HoursToMinutesLeapYear * 60;*/

		int ReadNumber() {
			int Number;
			cout << "\nEnter a Number? ";
			cin >> Number;
			return Number;
		}

		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		void PrintTimeStats(int year)
		{
			/*  if (IsLeapYear(year)) {
				  cout << "Number Of Days in Year     | [" << year << "] is " << YearToDays << endl;
				  cout << "Number Of hours in Year    | [" << year << "] is " << DaysToHours << endl;
				  cout << "Number Of Minutes in Year  | [" << year << "] is " << HoursToMinutes << endl;
				  cout << "Number Of Seconds in Year  | [" << year << "] is " << MinutesToSecons << endl;
			  }
			  else
			  {
				  cout << "Number Of Days in Year     | [" << year << "] is " << YearToDaysLeapYear << endl;
				  cout << "Number Of hours in Year    | [" << year << "] is " << DaysToHoursLeapYear << endl;
				  cout << "Number Of Minutes in Year  | [" << year << "] is " << HoursToMinutesLeapYear << endl;
				  cout << "Number Of Seconds in Year  | [" << year << "] is " << MinutesToSeconsLeapYear << endl;
			  }*/
		}

		int main() {

			int Year = ReadNumber();
			PrintTimeStats(Year);
			return 0;
		}
	};
	class Problem4 {
		int ReadNumber() {
			int Number;
			cout << "\nEnter a Number? ";
			cin >> Number;
			return Number;
		}

		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}
		int NumberOfDays(int year) {
			return IsLeapYear(year) ? 366 : 365;
		}

		int NumberOfHours(int year) {
			return NumberOfDays(year) * 24;
		}

		int NumberOfMinutes(int year) {
			return NumberOfHours(year) * 60;
		}

		int NumberOfSeconds(int year) {
			return NumberOfMinutes(year) * 60;
		}

		void PrintYearStats(int year) {
			cout << "Number Of Days in Year     | [" << year << "] is " << NumberOfDays(year) << endl;
			cout << "Number Of Hours in Year    | [" << year << "] is " << NumberOfHours(year) << endl;
			cout << "Number Of Minutes in Year  | [" << year << "] is " << NumberOfMinutes(year) << endl;
			cout << "Number Of Seconds in Year  | [" << year << "] is " << NumberOfSeconds(year) << endl;
		}

		int main() {
			int year = ReadNumber();
			PrintYearStats(year);
			return 0;
		}
	};
	class Problem5 {
		int ReadNumber(string message) {
			int Number;
			cout << message;
			cin >> Number;
			return Number;
		}
		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}
		int NumberOfDaysInMonth(int month, int year) {
			if (month < 1 || month > 12) return 0;

			if (month == 2)
				return IsLeapYear(year) ? 29 : 28;

			int arr31Days[7] = { 1,3,5,7,8,10,12 };
			for (int i = 0; i < 7; i++) {
				if (arr31Days[i] == month) return 31;
			}
			return 30;
		}
		int NumberOfHours(int year, int month) {
			return NumberOfDaysInMonth(month, year) * 24;
		}
		int NumberOfMinutes(int year, int month) {
			return NumberOfHours(year, month) * 60;
		}
		int NumberOfSeconds(int year, int month) {
			return NumberOfMinutes(year, month) * 60;
		}
		void PrintMonthStat(int year, int month) {
			cout << "Number Of Days in Month     | [" << month << "] is " << NumberOfDaysInMonth(month, year) << endl;
			cout << "Number Of Hours in Month    | [" << month << "] is " << NumberOfHours(year, month) << endl;
			cout << "Number Of Minutes in Month  | [" << month << "] is " << NumberOfMinutes(year, month) << endl;
			cout << "Number Of Seconds in Month  | [" << month << "] is " << NumberOfSeconds(year, month) << endl;
		}
		int main() {
			int year = ReadNumber("Please Number Of Year : ");
			int month = ReadNumber("Please Number Of Month : ");
			PrintMonthStat(year, month);
			return 0;
		}
	};
	class Problem6 {
		int ReadNumber(string message) {
			int Number;
			cout << message;
			cin >> Number;
			return Number;
		}
		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}
		int NumberOfDaysInMonth(int month, int year) {
			if (month < 1 || month > 12) return 0;

			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

			return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : arrDays[month - 1];
		}

		void PrintMonthStat(int year, int month) {
			cout << "Number Of Days in Month     | [" << month << "] is " << NumberOfDaysInMonth(month, year) << endl;
			//cout << "Number Of Hours in Month    | [" << month << "] is " << NumberOfHours(year, month) << endl;
			//cout << "Number Of Minutes in Month  | [" << month << "] is " << NumberOfMinutes(year, month) << endl;
			//cout << "Number Of Seconds in Month  | [" << month << "] is " << NumberOfSeconds(year, month) << endl;
		}

		int main() {
			int year = ReadNumber("Please Number Of Year : ");
			int month = ReadNumber("Please Number Of Month : ");
			PrintMonthStat(year, month);
			return 0;
		}
	};
	class Problem7 {
		int ReadNumber(string message) {
			int Number;
			cout << message;
			cin >> Number;
			return Number;
		}


		string GetDayName(int DayOfWeekOrder) {
			string names[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
			return names[DayOfWeekOrder];
		}
		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		int NumberOfDaysInMonth(int month, int year) {
			if (month < 1 || month > 12) return 0;

			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

			return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : arrDays[month - 1];
		}

		int GetDayIndex(int year, int month, int day) {
			int a = (14 - month) / 12;
			int y = year - a;
			int m = month + 12 * a - 2;
			return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
		}

		void PrintMonthStat(int year, int month, int day) {

			cout << "Date        : " << day << "/" << month << "/" << year << endl;
			cout << "Day Order   : " << GetDayIndex(year, month, day) << endl;
			cout << "Day Name    : " << GetDayName(GetDayIndex(year, month, day)) << endl;
		}

		int main() {
			int year = ReadNumber("Please Number Of Year : ");
			int month = ReadNumber("Please Number Of Month : ");
			int day = ReadNumber("Please Number Of Day : ");
			PrintMonthStat(year, month, day);
			return 0;
		}
	};
	class Problem8ReviewTheCourse {
		int ReadNumber(string message) {
			int Number;
			cout << message;
			cin >> Number;
			return Number;
		}

		string GetDayName(int DayOfWeekOrder) {
			string names[] = { "SUN","MON","TUES","WED","THU","FRI","SAT" };
			return names[DayOfWeekOrder];
		}

		string GetMonthName(int MonthOrder) {
			string names[] = { "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC" };
			return names[MonthOrder];
		}

		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		int NumberOfDaysInMonth(int month, int year) {
			if (month < 1 || month > 12) return 0;

			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

			return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : arrDays[month - 1];
		}

		int GetDayIndex(int year, int month, int day) {
			int a = (14 - month) / 12;
			int y = year - a;
			int m = month + 12 * a - 2;
			return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
		}

		void PrintDayNames() {
			for (int i = 0; i < 7; i++)
				cout << setw(4) << GetDayName(i);
			cout << endl;
		}

		void PrintDayNumber(int month, int year) {
			int startDay = GetDayIndex(year, month, 1);
			int days = NumberOfDaysInMonth(month, year);

			for (int i = 0; i < startDay; i++)
				cout << "    ";

			for (int day = 1; day <= days; day++)
			{
				cout << setw(4) << day;
				if ((startDay + day) % 7 == 0)
					cout << endl;
			}
			cout << endl;
		}

		void PrintMonthStat(int year, int month) {
			cout << "\n_____________" << GetMonthName(month) << "_____________" << endl;
			PrintDayNames();
			PrintDayNumber(month, year);
			cout << "_____________________________" << endl;
		}

		int main() {
			int year = ReadNumber("Please Number Of Year : ");
			int month = ReadNumber("\nPlease Number Of Month : ");
			PrintMonthStat(year, month);
			return 0;
		}
	};
	class Problem9 {
		int ReadNumber(string message) {
			int Number;
			cout << message;
			cin >> Number;
			return Number;
		}

		string GetDayName(int DayOfWeekOrder) {
			string names[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
			if (DayOfWeekOrder < 0 || DayOfWeekOrder > 6)
				return "InvalidDay";
			return names[DayOfWeekOrder];
		}

		string GetMonthName(int MonthOrder) {
			string names[] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
							   "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };
			if (MonthOrder < 1 || MonthOrder > 12)
				return "InvalidMonth";
			return names[MonthOrder - 1];
		}

		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		int NumberOfDaysInMonth(int month, int year) {
			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
			if (month == 2)
				return IsLeapYear(year) ? 29 : 28;
			return arrDays[month - 1];
		}

		int GetDayIndex(int year, int month, int day) {
			int a = (14 - month) / 12;
			int y = year - a;
			int m = month + 12 * a - 2;
			return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
		}

		void PrintDayNames() {
			for (int i = 0; i < 7; i++)
				cout << setw(4) << GetDayName(i);
			cout << endl;
		}

		void PrintDayNumber(int month, int year) {
			int startDay = GetDayIndex(year, month, 1);
			int days = NumberOfDaysInMonth(month, year);

			for (int i = 0; i < startDay; i++)
				cout << "    ";

			for (int day = 1; day <= days; day++) {
				cout << setw(4) << day;

				if ((startDay + day) % 7 == 0)
					cout << endl;
			}
			cout << endl;
		}

		void PrintMonthCalendar(int year, int month) {
			cout << "\n__________" << GetMonthName(month) << "__________" << endl;
			PrintDayNames();
			PrintDayNumber(month, year);
			cout << "_____________________________" << endl;
		}

		void PrintYearCalendar(int year) {
			cout << "______________________________" << endl;
			cout << "Calendar - " << year << endl;
			cout << "______________________________" << endl;

			for (int i = 1; i <= 12; i++) {
				PrintMonthCalendar(year, i);
				cout << endl;
			}
		}

		int main() {
			int year = ReadNumber("Please enter the year: ");
			PrintYearCalendar(year);
			return 0;
		}
	};
	class Problem10 {
		int ReadNumber(string message) {
			int Number;
			cout << message;
			cin >> Number;
			return Number;
		}

		string GetDayName(int DayOfWeekOrder) {
			string names[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
			if (DayOfWeekOrder < 0 || DayOfWeekOrder > 6)
				return "InvalidDay";
			return names[DayOfWeekOrder];
		}

		string GetMonthName(int MonthOrder) {
			string names[] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
							   "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };
			if (MonthOrder < 1 || MonthOrder > 12)
				return "InvalidMonth";
			return names[MonthOrder - 1];
		}

		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		int NumberOfDaysInMonth(int month, int year) {
			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
			if (month == 2)
				return IsLeapYear(year) ? 29 : 28;
			return arrDays[month - 1];
		}

		int GetDayIndex(int year, int month, int day) {
			int a = (14 - month) / 12;
			int y = year - a;
			int m = month + 12 * a - 2;
			return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
		}
		//
		void PrintDayNames() {
			for (int i = 0; i < 7; i++)
				cout << setw(4) << GetDayName(i);
			cout << endl;
		}

		void PrintDayNumber(int month, int year) {
			int startDay = GetDayIndex(year, month, 1);
			int days = NumberOfDaysInMonth(month, year);

			for (int i = 0; i < startDay; i++)
				cout << "    ";

			for (int day = 1; day <= days; day++) {
				cout << setw(4) << day;

				if ((startDay + day) % 7 == 0)
					cout << endl;
			}
			cout << endl;
		}

		void PrintMonthCalendar(int year, int month) {
			cout << "\n__________" << GetMonthName(month) << "__________" << endl;
			PrintDayNames();
			PrintDayNumber(month, year);
			cout << "_____________________________" << endl;
		}

		void PrintYearCalendar(int year) {
			cout << "______________________________" << endl;
			cout << "Calendar - " << year << endl;
			cout << "______________________________" << endl;

			for (int i = 1; i <= 12; i++) {
				PrintMonthCalendar(year, i);
				cout << endl;
			}
		}

		int PrintTotalDaysFromTheBeginningOfYear(int year, int month, int day) {

			int TotalDays = 0;

			for (int i = 1; i <= month - 1; i++)
			{
				TotalDays += NumberOfDaysInMonth(i, year);
			}
			TotalDays += day;
			return TotalDays;

		}

		int main() {
			int year = ReadNumber("Please enter the year: ");
			int month = ReadNumber("Please enter the month: ");
			int day = ReadNumber("Please enter the day: ");
			cout << "\nNumber Of Days from the begining of the year is : "
				<< PrintTotalDaysFromTheBeginningOfYear(year, month, day);
			return 0;
		}
	};
	class Problem11Review {
		int ReadNumber(string message) {
			int Number;
			cout << message;
			cin >> Number;
			return Number;
		}

		string GetDayName(int DayOfWeekOrder) {
			string names[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
			if (DayOfWeekOrder < 0 || DayOfWeekOrder > 6)
				return "InvalidDay";
			return names[DayOfWeekOrder];
		}

		string GetMonthName(int MonthOrder) {
			string names[] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
							   "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };
			if (MonthOrder < 1 || MonthOrder > 12)
				return "InvalidMonth";
			return names[MonthOrder - 1];
		}

		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		int NumberOfDaysInMonth(int month, int year) {
			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
			if (month == 2)
				return IsLeapYear(year) ? 29 : 28;
			return arrDays[month - 1];
		}

		int GetDayIndex(int year, int month, int day) {
			int a = (14 - month) / 12;
			int y = year - a;
			int m = month + 12 * a - 2;
			return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
		}

		void PrintDayNames() {
			for (int i = 0; i < 7; i++)
				cout << setw(4) << GetDayName(i);
			cout << endl;
		}

		void PrintDayNumber(int month, int year) {

			int startDay = GetDayIndex(year, month, 1);
			int days = NumberOfDaysInMonth(month, year);

			for (int i = 0; i < startDay; i++)
				cout << "    ";

			for (int day = 1; day <= days; day++) {
				cout << setw(4) << day;

				if ((startDay + day) % 7 == 0)
					cout << endl;
			}
			cout << endl;
		}

		void PrintMonthCalendar(int year, int month) {
			cout << "\n__________" << GetMonthName(month) << "__________" << endl;
			PrintDayNames();
			PrintDayNumber(month, year);
			cout << "_____________________________" << endl;
		}

		void PrintYearCalendar(int year) {
			cout << "______________________________" << endl;
			cout << "Calendar - " << year << endl;
			cout << "______________________________" << endl;

			for (int i = 1; i <= 12; i++) {
				PrintMonthCalendar(year, i);
				cout << endl;
			}
		}

		int PrintTotalDaysFromTheBeginningOfYear(int year, int month, int day) {

			int TotalDays = 0;

			for (int i = 1; i <= month - 1; i++)
			{
				TotalDays += NumberOfDaysInMonth(i, year);
			}
			TotalDays += day;
			return TotalDays;

		}

		void ConvertBackTotalDaysToDate(int totalOfDays, int year) {
			int month = 1;
			while (totalOfDays > NumberOfDaysInMonth(month, year)) {
				totalOfDays -= NumberOfDaysInMonth(month, year);
				month++;
			}

			int day = totalOfDays;

			cout << "\nConverted Date: " << day << "/" << month << "/" << year
				<< " (" << month << " ," << day << ", " << year << ")" << endl;
		}


		int main() {
			int year = ReadNumber("Please enter the year: ");
			int month = ReadNumber("Please enter the month: ");
			int day = ReadNumber("Please enter the day: ");

			int numberOfDays = PrintTotalDaysFromTheBeginningOfYear(year, month, day);
			cout << "\nNumber Of Days from the beginning of the year is : "
				<< numberOfDays << endl;

			ConvertBackTotalDaysToDate(numberOfDays, year);

			return 0;
		}
	};
	class Problem12Review {
		int ReadNumber(string message) {
			int Number;
			cout << message;
			cin >> Number;
			return Number;
		}

		struct sDate
		{
			int Year;
			int Month;
			int Day;
		};

		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		int NumberOfDaysInMonth(int month, int year) {
			if (month < 1 || month > 12)
				return 0;

			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

			if (month == 2)
				return IsLeapYear(year) ? 29 : 28;
			return arrDays[month - 1];
		}

		int PrintTotalDaysFromTheBeginningOfYear(int year, int month, int day) {

			int TotalDays = 0;

			for (int i = 1; i <= month - 1; i++)
			{
				TotalDays += NumberOfDaysInMonth(i, year);
			}
			TotalDays += day;
			return TotalDays;

		}

		sDate AddingDaysToDate(int Days, sDate Date) {

			int totalDays = Days + PrintTotalDaysFromTheBeginningOfYear(Date.Year, Date.Month, Date.Day);
			int MonthDays = 0;
			Date.Month = 1;
			while (true)
			{
				MonthDays = NumberOfDaysInMonth(Date.Month, Date.Year);

				if (totalDays > MonthDays) {
					totalDays -= MonthDays;
					Date.Month++;
					if (Date.Month > 12) {
						Date.Month = 1;
						Date.Year++;
					}
				}
				else
				{
					Date.Day = totalDays;
					break;
				}
			}
			return Date;
		}

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		int main() {
			sDate Date = ReadFullDate();
			int Days = ReadNumber("How many days to add : ");

			Date = AddingDaysToDate(Days, Date);

			cout << "\nDate after adding [" << Days << "] days is: ";
			cout << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			return 0;
		}

	};
	class Problem13Review {

		int ReadNumber(string message) {
			int Number;
			cout << message;
			cin >> Number;
			return Number;
		}

		struct sDate
		{
			int Year;
			int Month;
			int Day;
		};

		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		int NumberOfDaysInMonth(int month, int year) {
			if (month < 1 || month > 12)
				return 0;

			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

			if (month == 2)
				return IsLeapYear(year) ? 29 : 28;
			return arrDays[month - 1];
		}

		int PrintTotalDaysFromTheBeginningOfYear(int year, int month, int day) {

			int TotalDays = 0;

			for (int i = 1; i <= month - 1; i++)
			{
				TotalDays += NumberOfDaysInMonth(i, year);
			}
			TotalDays += day;
			return TotalDays;

		}

		bool CompareTwoDates(sDate Date1, sDate Date2) {
			return (Date1.Year > Date2.Year) ||
				(Date1.Year == Date2.Year && Date1.Month > Date2.Month) ||
				(Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day > Date2.Day);
		}


		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		int main() {
			sDate Date1 = ReadFullDate();
			sDate Date2 = ReadFullDate();


			if (!CompareTwoDates(Date1, Date2)) {
				cout << "Date1 is Less then Date2";
			}
			else
			{

				cout << "Date1 is Bigger then Date2";
			}


			return 0;
		}

	};
	class Problem14 {
		int ReadNumber(string message) {
			int Number;
			cout << message;
			cin >> Number;
			return Number;
		}

		struct sDate
		{
			int Year;
			int Month;
			int Day;
		};

		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		int NumberOfDaysInMonth(int month, int year) {
			if (month < 1 || month > 12)
				return 0;

			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

			if (month == 2)
				return IsLeapYear(year) ? 29 : 28;
			return arrDays[month - 1];
		}

		int PrintTotalDaysFromTheBeginningOfYear(int year, int month, int day) {

			int TotalDays = 0;

			for (int i = 1; i <= month - 1; i++)
			{
				TotalDays += NumberOfDaysInMonth(i, year);
			}
			TotalDays += day;
			return TotalDays;

		}

		bool IsDate1EqualDate2(sDate Date1, sDate Date2) {
			return(Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? (Date1.Day == Date2.Day) : false) : false;
		}

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		int main() {
			sDate Date1 = ReadFullDate();
			sDate Date2 = ReadFullDate();

			if (IsDate1EqualDate2(Date1, Date2)) {
				cout << "Date1 is equal to Date2" << endl;
			}
			else {
				cout << "Date1 is not equal to Date2" << endl;
			}

			return 0;
		}

	};
	class Problem15{
		int ReadNumber(string message) {
			int Number;
			cout << message;
			cin >> Number;
			return Number;
		}

		struct sDate
		{
			int Year;
			int Month;
			int Day;
		};

		bool IsLeapYear(int year) {
			return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		}

		int NumberOfDaysInMonth(int month, int year) {
			if (month < 1 || month > 12)
				return 0;

			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

			if (month == 2)
				return IsLeapYear(year) ? 29 : 28;
			return arrDays[month - 1];
		}

		int PrintTotalDaysFromTheBeginningOfYear(int year, int month, int day) {

			int TotalDays = 0;

			for (int i = 1; i <= month - 1; i++)
			{
				TotalDays += NumberOfDaysInMonth(i, year);
			}
			TotalDays += day;
			return TotalDays;

		}

		bool IsLastDayInMonth(int day, int month, int year) {

			if (NumberOfDaysInMonth(month, year) == day)
				return true;
			return false;

		}

		bool IsLastMonthInYear(int month) {

			if (month == 12)
				return true;
			return false;
		}

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		int main() {
			int day = ReadNumber("Please enter a Day : ");
			int month = ReadNumber("Please enter a Month : ");
			int year = ReadNumber("Please enter a Year : ");

			if (IsLastDayInMonth(day, month, year)) {

				cout << "\nYes , Day is last day in month. ";
			}
			else
			{
				cout << "\nNo , Day isn't last day in month. ";

			}

			if (IsLastMonthInYear(month)) {

				cout << "\nYes, Month is last Month in year";
			}
			else
			{
				cout << "\nNo, Month isn't last Month in year";

			}

			return 0;
		}
	};
}