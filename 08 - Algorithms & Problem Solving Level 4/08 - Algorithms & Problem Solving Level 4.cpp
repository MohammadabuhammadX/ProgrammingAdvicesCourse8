#pragma warning(disable : 4996)

#include <ctime>
#include <iostream>
#include <iomanip>
#include<vector>

using namespace std;

struct sDate
{
	int Year;
	int Month;
	int Day;
};
sDate IncreaseDateByOne(sDate Date);

enum enDateCompare { Before = -1, Equal = 0, After = 1 };

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

sDate ReadFullDate() {
	sDate Date;

	Date.Day = ReadNumber("\nPlease enter a Day : ");
	Date.Month = ReadNumber("\nPlease enter a Month : ");
	Date.Year = ReadNumber("\nPlease enter a Year : ");

	return Date;
}

bool IsLastDayInMonth(sDate Date) {

	return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));

}

bool IsLastMonthInYear(int month) {

	return (month == 12);
}

bool IsFirstDayInMonth(sDate Date) {
	return Date.Day == 1;
}

bool IsFirstMonthInYear(int month) {
	return (month == 1);
}

bool IsDate1EqualDate2(sDate Date1, sDate Date2) {
	return(Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? (Date1.Day == Date2.Day) : false) : false;
}

bool IsDate1BeforeDate2(sDate Date1, sDate Date2)//
{
	return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
		(Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ?
			Date1.Day < Date2.Day : false)) : false);
}

bool IsDate1AfterDate2(sDate Date1, sDate Date2)//
{
	return (Date1.Year > Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
		(Date1.Month > Date2.Month ? true : (Date1.Month == Date2.Month ?
			Date1.Day > Date2.Day : false)) : false);
}

bool IsDate1AfterDate2CourseApproach(sDate date1, sDate date2) {//

	return (!IsDate1BeforeDate2(date1, date2) && !IsDate1EqualDate2(date1, date2));

}

enDateCompare CompareDates(sDate date1, sDate date2) {


	if (IsDate1BeforeDate2(date1, date2))
		return enDateCompare::Before;

	if (IsDate1EqualDate2(date1, date2))
		return enDateCompare::Equal;

	return enDateCompare::After;
}

void SwapDates(sDate& date1, sDate& date2) {

	sDate TempDate;

	TempDate.Year = date1.Year;
	TempDate.Month = date1.Month;
	TempDate.Day = date1.Day;

	date1.Year = date2.Year;
	date1.Month = date2.Month;
	date1.Day = date2.Day;

	date2.Year = TempDate.Year;
	date2.Month = TempDate.Month;
	date2.Day = TempDate.Day;
}

int GetDifferenceInDays(sDate date, sDate date1, bool IncludeEndDay = false) {

	int days = 0;
	short swapFlagValue = 1;

	if (!IsDate1BeforeDate2(date, date1)) {
		SwapDates(date, date1);
		swapFlagValue = -1;
	}

	while (IsDate1BeforeDate2(date, date1))
	{
		days++;
		date = IncreaseDateByOne(date);
	}

	return IncludeEndDay ? ++days * swapFlagValue : days * swapFlagValue;
}

sDate IncreaseDateByOne(sDate Date) {

	if (IsLastDayInMonth(Date)) {
		if (IsLastMonthInYear(Date.Month)) {
			Date.Month = 1;
			Date.Day = 1;
			Date.Year++;
		}
		else
		{
			Date.Day = 1;
			Date.Month++;
		}
	}
	else
	{
		Date.Day++;
	}

	return Date;
}

int CompareTwoDates(sDate date, sDate date1, bool flag = false) {

	int total1Days = 0;
	int total2Days = 0;

	for (int i = 1; i <= date.Month - 1; i++)
	{
		total1Days += NumberOfDaysInMonth(i, date.Year);
	}
	total1Days += date.Day;


	for (int i = 1; i <= date1.Month - 1; i++)
	{
		total2Days += NumberOfDaysInMonth(i, date1.Year);
	}
	total2Days += date1.Day;


	return flag ? (abs(total1Days - total2Days) + 1) : abs(total1Days - total2Days);

}

string GetDayName(int DayOfWeekOrder) {
	string names[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
	return names[DayOfWeekOrder];
}

int GetDayIndex(int year, int month, int day) {
	int a = (14 - month) / 12;
	int y = year - a;
	int m = month + 12 * a - 2;
	return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
}

void PrintMonthStat(sDate Date) {

	cout << "Today is " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
		<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
}

void StartVacation(sDate Date) {

	cout << "/nVacation From : " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
		<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
}

void EndOfvacation(sDate Date) {

	cout << "\nVacation To " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
		<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
}

sDate GetSystemDate() {

	sDate date;

	time_t t = time(0);
	tm* now = localtime(&t);

	date.Year = now->tm_year + 1900;
	date.Month = now->tm_mon + 1;
	date.Day = now->tm_mday;

	return date;
}

bool IsEndOfWeek(sDate Date) {

	int dayIndex = GetDayIndex(Date.Year, Date.Month, Date.Day);

	return (dayIndex == 6);

}

bool IsWeekEnd(sDate Date) {

	int dayIndex = GetDayIndex(Date.Year, Date.Month, Date.Day);

	return (dayIndex == 5 || dayIndex == 6);

}

bool IsBusinessDay(sDate Date) {
	return  !IsWeekEnd(Date);
}

int DaysUntilEndOfWeek(sDate date) {

	int indexOfDay = GetDayIndex(date.Year, date.Month, date.Day);

	return (7 - (indexOfDay + 1));

}

int DaysUntilEndOfMonth(sDate date) {

	int numOfDaysInMonth = NumberOfDaysInMonth(date.Month, date.Year);

	return (numOfDaysInMonth - date.Day);

}

int NumberOfDays(int year) {
	return IsLeapYear(year) ? 366 : 365;
}

int DaysUntilEndOfYear(sDate Date) {

	int totalDays = PrintTotalDaysFromTheBeginningOfYear(Date.Year, Date.Month, Date.Day);

	return (NumberOfDays(Date.Year) - totalDays);

}

int GetActualVacationDays(sDate startDate, sDate endDate) {

	int ctr = 0;

	while (IsDate1BeforeDate2(startDate, endDate))
	{
		if (IsBusinessDay(startDate)) {
			ctr++;
		}
		startDate = IncreaseDateByOne(startDate);
	}
	return ctr;
}

sDate GetDayToReturnToWorks(int days, sDate date) {

	int ctr = 0;
	while (ctr < days)
	{
		if (IsBusinessDay(date)) {
			ctr++;
		}
		date = IncreaseDateByOne(date);
	}

	return date;

}

bool OverlapTwoPeriods(sDate startDate1, sDate endDate1, sDate startDate2, sDate endDate2) {

	if (CompareDates(startDate1, endDate1) == enDateCompare::Before ||
		CompareDates(startDate2, endDate2) == enDateCompare::After)
		return false;
	else
		return true;
}

int PeriodLengthInDays(sDate startDate, sDate endDate, bool IncludeEndDate = false) {
	return GetDifferenceInDays(startDate, endDate, IncludeEndDate);
}

int main() {

	cout << "First Periods : " << endl;;

	cout << "\nEnter Start Date1 : ";
	sDate startDate1 = ReadFullDate();
	cout << "\nEnter End Date1 : ";
	sDate endDate1 = ReadFullDate();

	cout << "\nEnter Start Date1 : ";
	sDate startDate2 = ReadFullDate();
	cout << "\nEnter End Date1 : ";
	sDate endDate2 = ReadFullDate();

	cout << "\nPeriod Length is : " << PeriodLengthInDays(startDate1, endDate1);
	cout << "\nPeriod Length (Including End Date) is : " << PeriodLengthInDays(startDate1, endDate1, true);

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
	class Problem15 {
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
	class Problem16Review {
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

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		bool IsLastDayInMonth(sDate Date) {

			return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));

		}

		bool IsLastMonthInYear(int month) {

			return (month == 12);
		}

		sDate IncreaseDateByOne(sDate Date) {

			if (IsLastDayInMonth(Date)) {
				if (IsLastMonthInYear(Date.Month)) {
					Date.Month = 1;
					Date.Day = 1;
					Date.Year++;
				}
				else
				{
					Date.Day = 1;
					Date.Month++;
				}
			}
			else
			{
				Date.Day++;
			}

			return Date;
		}

		int main() {
			sDate Date = ReadFullDate();
			sDate NextDate = IncreaseDateByOne(Date);

			cout << "\nNext Date: " << NextDate.Day << "/" << NextDate.Month << "/" << NextDate.Year << endl;

			return 0;
		}
	};
	class Problem17Review {
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

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		bool IsLastDayInMonth(sDate Date) {

			return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));

		}

		bool IsLastMonthInYear(int month) {

			return (month == 12);
		}

		bool IsDate1BeforeDate2(sDate Date1, sDate Date2)
		{
			return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
				(Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ?
					Date1.Day < Date2.Day : false)) : false);
		}

		sDate IncreaseDateByOne(sDate Date) {

			if (IsLastDayInMonth(Date)) {
				if (IsLastMonthInYear(Date.Month)) {
					Date.Month = 1;
					Date.Day = 1;
					Date.Year++;
				}
				else
				{
					Date.Day = 1;
					Date.Month++;
				}
			}
			else
			{
				Date.Day++;
			}

			return Date;
		}

		int GetDifferenceInDays(sDate date, sDate date1, bool IncludeEndDay = false) {

			int days = 0;
			while (IsDate1BeforeDate2(date, date1))
			{
				days++;
				date = IncreaseDateByOne(date);  // ✅ FIX: increment date, not date1
			}

			return IncludeEndDay ? ++days : days;
		}

		int CompareTwoDates(sDate date, sDate date1, bool flag = false) {

			int total1Days = 0;
			int total2Days = 0;

			for (int i = 1; i <= date.Month - 1; i++)
			{
				total1Days += NumberOfDaysInMonth(i, date.Year);
			}
			total1Days += date.Day;


			for (int i = 1; i <= date1.Month - 1; i++)
			{
				total2Days += NumberOfDaysInMonth(i, date1.Year);
			}
			total2Days += date1.Day;


			return flag ? (abs(total1Days - total2Days) + 1) : abs(total1Days - total2Days);

		}

		int main() {
			sDate Date = ReadFullDate();
			sDate Date1 = ReadFullDate();

			cout << "\nDifference is : " << GetDifferenceInDays(Date, Date1) << "Day(s).";

			cout << "\nDifference is (Include End Day) is: " << GetDifferenceInDays(Date, Date1, true) << "Day(s).";

			return 0;
		}
	};
	class Problem18Review {
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

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		bool IsLastDayInMonth(sDate Date) {

			return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));

		}

		bool IsLastMonthInYear(int month) {

			return (month == 12);
		}

		bool IsDate1BeforeDate2(sDate Date1, sDate Date2)
		{
			return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
				(Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ?
					Date1.Day < Date2.Day : false)) : false);
		}

		sDate IncreaseDateByOne(sDate Date) {

			if (IsLastDayInMonth(Date)) {
				if (IsLastMonthInYear(Date.Month)) {
					Date.Month = 1;
					Date.Day = 1;
					Date.Year++;
				}
				else
				{
					Date.Day = 1;
					Date.Month++;
				}
			}
			else
			{
				Date.Day++;
			}

			return Date;
		}

		int GetDifferenceInDays(sDate date, sDate date1, bool IncludeEndDay = false) {

			int days = 0;
			while (IsDate1BeforeDate2(date, date1))
			{
				days++;
				date = IncreaseDateByOne(date);  // ✅ FIX: increment date, not date1
			}

			return IncludeEndDay ? ++days : days;
		}

		int CompareTwoDates(sDate date, sDate date1, bool flag = false) {

			int total1Days = 0;
			int total2Days = 0;

			for (int i = 1; i <= date.Month - 1; i++)
			{
				total1Days += NumberOfDaysInMonth(i, date.Year);
			}
			total1Days += date.Day;


			for (int i = 1; i <= date1.Month - 1; i++)
			{
				total2Days += NumberOfDaysInMonth(i, date1.Year);
			}
			total2Days += date1.Day;


			return flag ? (abs(total1Days - total2Days) + 1) : abs(total1Days - total2Days);

		}

		sDate GetSystemDate() {

			sDate date;

			time_t t = time(0);
			tm* now = localtime(&t);

			date.Year = now->tm_year + 1900;
			date.Month = now->tm_mon + 1;
			date.Day = now->tm_mday;

			return date;
		}

		int main() {

			sDate Date = ReadFullDate();
			cout << "\nPlease Enter Your Date Of Birth :\n";

			sDate Date1 = GetSystemDate();
			cout << "\nYour Age is : " << GetDifferenceInDays(Date, Date1, true) << "Day(s).";
			return 0;
		}
	};
	class Problems20To32 {
		struct sDate
		{
			int Year;
			int Month;
			int Day;
		};

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
			if (month < 1 || month > 12)
				return 0;

			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

			if (month == 2)
				return IsLeapYear(year) ? 29 : 28;
			return arrDays[month - 1];
		}

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		bool IsLastDayInMonth(sDate Date) {

			return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));

		}

		bool IsLastMonthInYear(int month) {

			return (month == 12);
		}

		sDate IncreaseDateByOne(sDate Date) {

			if (IsLastDayInMonth(Date)) {
				if (IsLastMonthInYear(Date.Month)) {
					Date.Month = 1;
					Date.Day = 1;
					Date.Year++;
				}
				else
				{
					Date.Day = 1;
					Date.Month++;
				}
			}
			else
			{
				Date.Day++;
			}

			return Date;
		}

		sDate IncreaseDateByXDays(sDate Date, int day) {


			for (int i = 1; i <= day; i++)
			{
				Date = IncreaseDateByOne(Date);
			}

			return Date;
		}

		sDate IncreaseDateByOneWeek(sDate Date) {

			for (int i = 0; i < 7; i++)
			{
				Date = IncreaseDateByOne(Date);
			}
			return Date;
		}

		sDate IncreaseDateByXWeeks(int Week, sDate Date) {

			for (int i = 0; i < Week; i++)
			{
				Date = IncreaseDateByOneWeek(Date);
			}

			return Date;
		}

		sDate IncreaseDateByOneMonth(sDate Date) {

			if (Date.Month == 12) {
				Date.Month = 1;
				Date.Year++;
			}
			// 31/1/2022
			//31/2/2022
			//
			else
			{
				Date.Month++;
			}

			int NumberOfDayInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

			if (Date.Day > NumberOfDayInCurrentMonth) {
				Date.Day = NumberOfDayInCurrentMonth;
			}

			return Date;
		}

		sDate IncreaseDateByXMonths(int numOfMonth, sDate Date) {

			for (int i = 0; i < numOfMonth; i++)
			{
				Date = IncreaseDateByOneMonth(Date);
			}

			return Date;

		}

		sDate IncreaseDateByOneYear(sDate Date) {

			Date.Year++;

			return Date;

		}

		sDate IncreaseDateByXYears(int year, sDate Date) {

			for (int i = 0; i < year; i++)
			{
				Date = IncreaseDateByOneYear(Date);
			}

			return Date;
		}

		sDate IncreaseDateByxYearsFaster(int year, sDate Date) {

			/*int ctr = 0;

			do
			{

				Date.Year++;
				ctr++;

			} while (ctr < year);*/

			Date.Year += year;

			if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
				Date.Day = 28;
			}

			return Date;
		}

		sDate IncreaseDateByOneDecade(sDate Date) {

			Date.Year += 10;

			return Date;
		}

		sDate IncreaseDateByXDecade(int numOfDecade, sDate Date) {

			for (int i = 0; i < numOfDecade; i++)
			{
				Date = IncreaseDateByOneDecade(Date);
			}

			return Date;
		}

		sDate IncreaseDateByXDecadeFaster(int numOfDecade, sDate Date) {

			Date.Year += numOfDecade * 10;

			return Date;
		}

		sDate IncreaseDateByOneCentury(sDate Date) {

			Date.Year += 100;
			return Date;
		}

		sDate IncreaseDateByOneMillennium(sDate Date) {

			Date.Year += 1000;
			return Date;
		}

		int main() {
			sDate Date = ReadFullDate();

			Date = IncreaseDateByOne(Date);
			cout << "\n01 - Adding one day is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			int inputForDay = ReadNumber("How many days do you want to add : ");
			Date = IncreaseDateByXDays(Date, inputForDay);
			cout << "\n02 - Adding " << inputForDay << " days is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			Date = IncreaseDateByOneWeek(Date);
			cout << "\n03 - Adding one week is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			int inputForWeeks = ReadNumber("How many weeks do you want to add : ");
			Date = IncreaseDateByXWeeks(inputForWeeks, Date);
			cout << "\n04 - Adding " << inputForWeeks << " weeks is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			Date = IncreaseDateByOneMonth(Date);
			cout << "\n05 - Adding one month is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			int inputForMonths = ReadNumber("How many months do you want to add : ");
			Date = IncreaseDateByXMonths(inputForMonths, Date);
			cout << "\n06 - Adding " << inputForMonths << " months is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			Date = IncreaseDateByOneYear(Date);
			cout << "\n07 - Adding one year is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			int inputForYears = ReadNumber("How many years do you want to add : ");
			Date = IncreaseDateByXYears(inputForYears, Date);
			cout << "\n08 - Adding " << inputForYears << " years is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			int inputForYearsFast = ReadNumber("How many years (faster) do you want to add : ");
			Date = IncreaseDateByxYearsFaster(inputForYearsFast, Date);
			cout << "\n09 - Adding " << inputForYearsFast << " years (faster) is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			Date = IncreaseDateByOneDecade(Date);
			cout << "\n10 - Adding one decade is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			int inputForDecades = ReadNumber("How many decades do you want to add : ");
			Date = IncreaseDateByXDecade(inputForDecades, Date);
			cout << "\n11 - Adding " << inputForDecades << " decades is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			int inputForDecadesFast = ReadNumber("How many decades (faster) do you want to add : ");
			Date = IncreaseDateByXDecadeFaster(inputForDecadesFast, Date);
			cout << "\n12 - Adding " << inputForDecadesFast << " decades (faster) is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			Date = IncreaseDateByOneCentury(Date);
			cout << "\n13 - Adding one century is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			Date = IncreaseDateByOneMillennium(Date);
			cout << "\n14 - Adding one millennium is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

			return 0;
		}
	};
	class Problems33To46 {

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
			if (month < 1 || month > 12)
				return 0;

			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

			if (month == 2)
				return IsLeapYear(year) ? 29 : 28;
			return arrDays[month - 1];
		}

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		bool IsFirstDayInMonth(sDate Date) {
			return Date.Day == 1;
		}

		bool IsFirstMonthInYear(int month) {
			return (month == 1);
		}

		int CompareTwoDates(sDate date, sDate date1, bool flag = false) {

			int total1Days = 0;
			int total2Days = 0;

			for (int i = 1; i <= date.Month - 1; i++)
			{
				total1Days += NumberOfDaysInMonth(i, date.Year);
			}
			total1Days += date.Day;


			for (int i = 1; i <= date1.Month - 1; i++)
			{
				total2Days += NumberOfDaysInMonth(i, date1.Year);
			}
			total2Days += date1.Day;


			return flag ? (abs(total1Days - total2Days) + 1) : abs(total1Days - total2Days);

		}

		sDate GetSystemDate() {

			sDate date;

			time_t t = time(0);
			tm* now = localtime(&t);

			date.Year = now->tm_year + 1900;
			date.Month = now->tm_mon + 1;
			date.Day = now->tm_mday;

			return date;
		}

		sDate DecreaseDateByOne(sDate Date) {

			if (IsFirstDayInMonth(Date)) {
				if (IsFirstMonthInYear(Date.Month)) {
					Date.Month = 12;
					Date.Day = 31;
					Date.Year--;
				}
				else
				{
					Date.Month--;
					Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
				}
			}
			else
			{
				Date.Day--;
			}

			return Date;
		}

		sDate DecreaseDateByXDays(sDate Date, int day) {


			for (int i = 0; i < day; i++)
			{
				Date = DecreaseDateByOne(Date);
			}
			return Date;
		}

		sDate DecreaseDateByOneWeek(sDate Date) {

			for (int i = 1; i <= 7; i++)
			{
				Date = DecreaseDateByOne(Date);
			}
			return Date;
		}

		sDate DecreaseDateByXWeeks(int Week, sDate Date) {

			for (int i = 1; i <= Week; i++)
			{
				Date = DecreaseDateByOneWeek(Date);
			}

			return Date;
		}

		sDate DecreaseDateByOneMonth(sDate Date) {

			if (Date.Month == 1) {
				Date.Month = 12;
				Date.Year--;
			}
			else
			{
				Date.Month--;
			}

			int NumberOfDayInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

			if (Date.Day > NumberOfDayInCurrentMonth) {
				Date.Day = NumberOfDayInCurrentMonth;
			}

			return Date;
		}

		sDate DecreaseDateByXMonths(int numOfMonth, sDate Date) {

			for (int i = 1; i <= numOfMonth; i++)
			{
				Date = DecreaseDateByOneMonth(Date);
			}

			return Date;

		}

		sDate DecreaseDateByOneYear(sDate Date) {

			Date.Year--;

			return Date;

		}

		sDate DecreaseDateByXYears(int year, sDate Date) {

			for (int i = 1; i <= year; i++)
			{
				Date = DecreaseDateByOneYear(Date);
			}

			return Date;
		}

		sDate DecreaseDateByxYearsFaster(int year, sDate Date) {

			/*int ctr = 0;

			do
			{

				Date.Year++;
				ctr++;

			} while (ctr < year);*/

			Date.Year -= year;

			if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year)) {
				Date.Day = 28;
			}

			return Date;
		}

		sDate DecreaseDateByOneDecade(sDate Date) {

			Date.Year -= 10;

			return Date;
		}

		sDate DecreaseDateByXDecade(int numOfDecade, sDate Date) {

			for (int i = 1; i <= numOfDecade; i++)
			{
				Date = DecreaseDateByOneDecade(Date);
			}

			return Date;
		}

		sDate DecreaseDateByXDecadeFaster(int numOfDecade, sDate Date) {

			Date.Year -= numOfDecade * 10;

			return Date;
		}

		sDate DecreaseDateByOneCentury(sDate Date) {

			Date.Year -= 100;
			return Date;
		}

		sDate DecreaseDateByOneMillennium(sDate Date) {

			Date.Year -= 1000;
			return Date;
		}

		int main() {
			sDate tempDate = ReadFullDate();

			tempDate = DecreaseDateByOne(tempDate);
			cout << "01 - Decreasing one day: " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByXDays(tempDate, 10);
			cout << "02 - Decreasing 10 days: " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByOneWeek(tempDate);
			cout << "03 - Decreasing one week: " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByXWeeks(10, tempDate);
			cout << "04 - Decreasing 10 weeks: " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByOneMonth(tempDate);
			cout << "05 - Decreasing one month: " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByXMonths(5, tempDate);
			cout << "06 - Decreasing 10 months: " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByOneYear(tempDate);
			cout << "07 - Decreasing one year: " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByXYears(10, tempDate);
			cout << "08 - Decreasing 10 years: " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByxYearsFaster(10, tempDate);
			cout << "09 - Decreasing 10 years (fast): " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByOneDecade(tempDate);
			cout << "10 - Decreasing one decade: " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByXDecade(10, tempDate);
			cout << "11 - Decreasing 10 decades: " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByXDecadeFaster(10, tempDate);
			cout << "12 - Decreasing 10 decades (fast): " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByOneCentury(tempDate);
			cout << "13 - Decreasing one century: " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			tempDate = DecreaseDateByOneMillennium(tempDate);
			cout << "14 - Decreasing one millennium: " << tempDate.Day << "/" << tempDate.Month << "/" << tempDate.Year << endl;

			return 0;
		}
	};
	class Problem47To53 {
		struct sDate
		{
			int Year;
			int Month;
			int Day;
		};

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

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		string GetDayName(int DayOfWeekOrder) {
			string names[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
			return names[DayOfWeekOrder];
		}

		int GetDayIndex(int year, int month, int day) {
			int a = (14 - month) / 12;
			int y = year - a;
			int m = month + 12 * a - 2;
			return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
		}

		void PrintMonthStat(sDate Date) {

			cout << "Today is " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		sDate GetSystemDate() {

			sDate date;

			time_t t = time(0);
			tm* now = localtime(&t);

			date.Year = now->tm_year + 1900;
			date.Month = now->tm_mon + 1;
			date.Day = now->tm_mday;

			return date;
		}

		bool IsEndOfWeek(sDate Date) {

			int dayIndex = GetDayIndex(Date.Year, Date.Month, Date.Day);

			return (dayIndex == 6);

		}

		bool IsWeekEnd(sDate Date) {

			int dayIndex = GetDayIndex(Date.Year, Date.Month, Date.Day);

			return (dayIndex == 5 || dayIndex == 6);

		}

		bool IsBusinessDay(sDate Date) {
			return  !IsWeekEnd(Date);
		}

		int DaysUntilEndOfWeek(sDate date) {

			int indexOfDay = GetDayIndex(date.Year, date.Month, date.Day);

			return (7 - (indexOfDay + 1));

		}

		int DaysUntilEndOfMonth(sDate date) {

			int numOfDaysInMonth = NumberOfDaysInMonth(date.Month, date.Year);

			return (numOfDaysInMonth - date.Day);

		}
		int NumberOfDays(int year) {
			return IsLeapYear(year) ? 366 : 365;
		}

		int DaysUntilEndOfYear(sDate Date) {

			int totalDays = PrintTotalDaysFromTheBeginningOfYear(Date.Year, Date.Month, Date.Day);

			return (NumberOfDays(Date.Year) - totalDays);

		}

		int main() {
			sDate tempDate = GetSystemDate();

			PrintMonthStat(tempDate);

			cout << "\nIs it End of week? ";
			if (!IsEndOfWeek(tempDate)) {
				cout << "No, Not End of week";
			}
			else {
				cout << "Yes, End Of week";
			}

			cout << "\nIs it Weekend? ";
			if (!IsWeekEnd(tempDate)) {
				cout << "No, Not Weekend";
			}
			else {
				cout << "Yes, It is Weekend";
			}

			cout << "\nIs it Business day? ";
			if (!IsBusinessDay(tempDate)) {
				cout << "No, it is Not business day";
			}
			else {
				cout << "Yes, It is business day";
			}

			int numOfDays = DaysUntilEndOfWeek(tempDate);
			cout << "\nDays Until end of week: " << numOfDays << " Day(s)." << endl;

			int numOfDaysUntilEndOfMonth = DaysUntilEndOfMonth(tempDate);
			cout << "Days Until End of month: " << numOfDaysUntilEndOfMonth << " Day(s)." << endl;

			int numOfDaysUntilEndOfYear = DaysUntilEndOfYear(tempDate);
			cout << "Days Until End of Year: " << numOfDaysUntilEndOfYear << " Day(s)." << endl;

			return 0;
		}

	};
	class Problem54 {
		struct sDate
		{
			int Year;
			int Month;
			int Day;
		};

		sDate IncreaseDateByOne(sDate Date) {
			if (IsLastDayInMonth(Date)) {
				if (IsLastMonthInYear(Date.Month)) {
					Date.Month = 1;
					Date.Day = 1;
					Date.Year++;
				}
				else {
					Date.Day = 1;
					Date.Month++;
				}
			}
			else {
				Date.Day++;
			}
			return Date;
		}

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
			if (month < 1 || month > 12)
				return 0;

			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

			if (month == 2)
				return IsLeapYear(year) ? 29 : 28;
			return arrDays[month - 1];
		}

		int PrintTotalDaysFromTheBeginningOfYear(int year, int month, int day) {
			int TotalDays = 0;
			for (int i = 1; i <= month - 1; i++) {
				TotalDays += NumberOfDaysInMonth(i, year);
			}
			TotalDays += day;
			return TotalDays;
		}

		sDate ReadFullDate() {
			sDate Date;
			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");
			return Date;
		}

		bool IsLastDayInMonth(sDate Date) {
			return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));
		}

		bool IsLastMonthInYear(int month) {
			return (month == 12);
		}

		bool IsFirstDayInMonth(sDate Date) {
			return Date.Day == 1;
		}

		bool IsFirstMonthInYear(int month) {
			return (month == 1);
		}

		bool IsDate1BeforeDate2(sDate Date1, sDate Date2) {
			return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
				(Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ?
					Date1.Day < Date2.Day : false)) : false);
		}

		void SwapDates(sDate& date1, sDate& date2) {
			sDate TempDate;
			TempDate.Year = date1.Year;
			TempDate.Month = date1.Month;
			TempDate.Day = date1.Day;

			date1.Year = date2.Year;
			date1.Month = date2.Month;
			date1.Day = date2.Day;

			date2.Year = TempDate.Year;
			date2.Month = TempDate.Month;
			date2.Day = TempDate.Day;
		}

		int GetDifferenceInDays(sDate date, sDate date1, bool IncludeEndDay = false) {
			int days = 0;
			short swapFlagValue = 1;

			if (!IsDate1BeforeDate2(date, date1)) {
				SwapDates(date, date1);
				swapFlagValue = -1;
			}

			while (IsDate1BeforeDate2(date, date1)) {
				days++;
				date = IncreaseDateByOne(date);
			}

			return IncludeEndDay ? ++days * swapFlagValue : days * swapFlagValue;
		}

		string GetDayName(int DayOfWeekOrder) {
			string names[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
			return names[DayOfWeekOrder];
		}

		int GetDayIndex(int year, int month, int day) {
			int a = (14 - month) / 12;
			int y = year - a;
			int m = month + 12 * a - 2;
			return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
		}

		void StartVacation(sDate Date) {
			cout << "\nVacation From : " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		void EndOfvacation(sDate Date) {
			cout << "\nVacation To : " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		bool IsWeekEnd(sDate Date) {
			int dayIndex = GetDayIndex(Date.Year, Date.Month, Date.Day);
			return (dayIndex == 5 || dayIndex == 6);
		}

		bool IsBusinessDay(sDate Date) {
			return !IsWeekEnd(Date);
		}

		int GetActualVacationDays(sDate startDate, sDate endDate) {
			int ctr = 0;
			while (IsDate1BeforeDate2(startDate, endDate)) {
				if (IsBusinessDay(startDate)) {
					ctr++;
				}
				startDate = IncreaseDateByOne(startDate);
			}
			return ctr;
		}

		int main() {
			sDate startDate;
			sDate endDate;

			cout << "\nVacation Starts : " << endl;
			startDate = ReadFullDate();

			cout << "\nVacation Ends : " << endl;
			endDate = ReadFullDate();

			StartVacation(startDate);
			EndOfvacation(endDate);

			int vacationDays = GetActualVacationDays(startDate, endDate);
			cout << "Actual business days: " << vacationDays << endl;

			return 0;
		}
	};
	class Problem55 {
		/*struct sDate
		{
			int Year;
			int Month;
			int Day;
		};

		sDate IncreaseDateByOne(sDate Date);

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
			if (month < 1 || month > 12)
				return 0;

			int arrDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

			if (month == 2)
				return IsLeapYear(year) ? 29 : 28;
			return arrDays[month - 1];
		}

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		bool IsLastDayInMonth(sDate Date) {

			return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));

		}

		bool IsLastMonthInYear(int month) {

			return (month == 12);
		}

		bool IsFirstDayInMonth(sDate Date) {
			return Date.Day == 1;
		}

		bool IsFirstMonthInYear(int month) {
			return (month == 1);
		}

		sDate IncreaseDateByOne(sDate Date) {

			if (IsLastDayInMonth(Date)) {
				if (IsLastMonthInYear(Date.Month)) {
					Date.Month = 1;
					Date.Day = 1;
					Date.Year++;
				}
				else
				{
					Date.Day = 1;
					Date.Month++;
				}
			}
			else
			{
				Date.Day++;
			}

			return Date;
		}

		string GetDayName(int DayOfWeekOrder) {
			string names[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
			return names[DayOfWeekOrder];
		}

		int GetDayIndex(int year, int month, int day) {
			int a = (14 - month) / 12;
			int y = year - a;
			int m = month + 12 * a - 2;
			return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
		}

		void PrintMonthStat(sDate Date) {

			cout << "Today is " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		void StartVacation(sDate Date) {

			cout << "/nVacation From : " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		void EndOfvacation(sDate Date) {

			cout << "\nVacation To " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		bool IsWeekEnd(sDate Date) {

			int dayIndex = GetDayIndex(Date.Year, Date.Month, Date.Day);

			return (dayIndex == 5 || dayIndex == 6);

		}

		bool IsBusinessDay(sDate Date) {
			return  !IsWeekEnd(Date);
		}

		sDate GetDayToReturnToWorks(int days, sDate date) {

			int ctr = 0;
			while (ctr < days)
			{
				if (IsBusinessDay(date)) {
					ctr++;
				}
				date = IncreaseDateByOne(date);
			}

			return date;

		}

		int main() {

			sDate startDate;

			cout << "Vaction Starts : " << endl;
			startDate = ReadFullDate();

			int userInputVacDays = ReadNumber("\nPlease Enter vacation days : ");

			sDate returnDate = GetDayToReturnToWorks(userInputVacDays, startDate);

			int dayIndex = GetDayIndex(returnDate.Year, returnDate.Month, returnDate.Day);

			cout << "Return Date : " << GetDayName(dayIndex) << " "
				<< returnDate.Day << "/" << returnDate.Month << "/" << returnDate.Year << endl;

			return 0;
		}*/
	};
	class Problem56 {

		struct sDate
		{
			int Year;
			int Month;
			int Day;
		};
		//sDate IncreaseDateByOne(sDate Date);
		sDate IncreaseDateByOne(sDate Date) {

			if (IsLastDayInMonth(Date)) {
				if (IsLastMonthInYear(Date.Month)) {
					Date.Month = 1;
					Date.Day = 1;
					Date.Year++;
				}
				else
				{
					Date.Day = 1;
					Date.Month++;
				}
			}
			else
			{
				Date.Day++;
			}

			return Date;
		}

		enum enDateCompare { Before = -1, Equal = 0, After = 1 };

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

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		bool IsLastDayInMonth(sDate Date) {

			return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));

		}

		bool IsLastMonthInYear(int month) {

			return (month == 12);
		}

		bool IsFirstDayInMonth(sDate Date) {
			return Date.Day == 1;
		}

		bool IsFirstMonthInYear(int month) {
			return (month == 1);
		}

		bool IsDate1EqualDate2(sDate Date1, sDate Date2) {
			return(Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? (Date1.Day == Date2.Day) : false) : false;
		}

		bool IsDate1BeforeDate2(sDate Date1, sDate Date2)//
		{
			return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
				(Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ?
					Date1.Day < Date2.Day : false)) : false);
		}
		bool IsDate1AfterDate2(sDate Date1, sDate Date2)//
		{
			return (Date1.Year > Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
				(Date1.Month > Date2.Month ? true : (Date1.Month == Date2.Month ?
					Date1.Day > Date2.Day : false)) : false);
		}

		bool IsDate1AfterDate2CourseApproach(sDate date1, sDate date2) {//

			return (!IsDate1BeforeDate2(date1, date2) && !IsDate1EqualDate2(date1, date2));

		}

		enDateCompare CompareDates(sDate date1, sDate date2) {//


			if (IsDate1BeforeDate2(date1, date2))
				return enDateCompare::Before;

			if (IsDate1EqualDate2(date1, date2))
				return enDateCompare::Equal;

			return enDateCompare::After;
		}

		void SwapDates(sDate& date1, sDate& date2) {

			sDate TempDate;

			TempDate.Year = date1.Year;
			TempDate.Month = date1.Month;
			TempDate.Day = date1.Day;

			date1.Year = date2.Year;
			date1.Month = date2.Month;
			date1.Day = date2.Day;

			date2.Year = TempDate.Year;
			date2.Month = TempDate.Month;
			date2.Day = TempDate.Day;
		}

		int GetDifferenceInDays(sDate date, sDate date1, bool IncludeEndDay = false) {

			int days = 0;
			short swapFlagValue = 1;

			if (!IsDate1BeforeDate2(date, date1)) {
				SwapDates(date, date1);
				swapFlagValue = -1;
			}

			while (IsDate1BeforeDate2(date, date1))
			{
				days++;
				date = IncreaseDateByOne(date);
			}

			return IncludeEndDay ? ++days * swapFlagValue : days * swapFlagValue;
		}


		int CompareTwoDates(sDate date, sDate date1, bool flag = false) {

			int total1Days = 0;
			int total2Days = 0;

			for (int i = 1; i <= date.Month - 1; i++)
			{
				total1Days += NumberOfDaysInMonth(i, date.Year);
			}
			total1Days += date.Day;


			for (int i = 1; i <= date1.Month - 1; i++)
			{
				total2Days += NumberOfDaysInMonth(i, date1.Year);
			}
			total2Days += date1.Day;


			return flag ? (abs(total1Days - total2Days) + 1) : abs(total1Days - total2Days);

		}

		string GetDayName(int DayOfWeekOrder) {
			string names[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
			return names[DayOfWeekOrder];
		}

		int GetDayIndex(int year, int month, int day) {
			int a = (14 - month) / 12;
			int y = year - a;
			int m = month + 12 * a - 2;
			return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
		}

		void PrintMonthStat(sDate Date) {

			cout << "Today is " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		void StartVacation(sDate Date) {

			cout << "/nVacation From : " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		void EndOfvacation(sDate Date) {

			cout << "\nVacation To " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		sDate GetSystemDate() {

			sDate date;

			time_t t = time(0);
			tm* now = localtime(&t);

			date.Year = now->tm_year + 1900;
			date.Month = now->tm_mon + 1;
			date.Day = now->tm_mday;

			return date;
		}

		bool IsEndOfWeek(sDate Date) {

			int dayIndex = GetDayIndex(Date.Year, Date.Month, Date.Day);

			return (dayIndex == 6);

		}

		bool IsWeekEnd(sDate Date) {

			int dayIndex = GetDayIndex(Date.Year, Date.Month, Date.Day);

			return (dayIndex == 5 || dayIndex == 6);

		}

		bool IsBusinessDay(sDate Date) {
			return  !IsWeekEnd(Date);
		}

		int DaysUntilEndOfWeek(sDate date) {

			int indexOfDay = GetDayIndex(date.Year, date.Month, date.Day);

			return (7 - (indexOfDay + 1));

		}

		int DaysUntilEndOfMonth(sDate date) {

			int numOfDaysInMonth = NumberOfDaysInMonth(date.Month, date.Year);

			return (numOfDaysInMonth - date.Day);

		}

		int NumberOfDays(int year) {
			return IsLeapYear(year) ? 366 : 365;
		}

		int DaysUntilEndOfYear(sDate Date) {

			int totalDays = PrintTotalDaysFromTheBeginningOfYear(Date.Year, Date.Month, Date.Day);

			return (NumberOfDays(Date.Year) - totalDays);

		}

		int GetActualVacationDays(sDate startDate, sDate endDate) {

			int ctr = 0;

			while (IsDate1BeforeDate2(startDate, endDate))
			{
				if (IsBusinessDay(startDate)) {
					ctr++;
				}
				startDate = IncreaseDateByOne(startDate);
			}
			return ctr;
		}

		sDate GetDayToReturnToWorks(int days, sDate date) {

			int ctr = 0;
			while (ctr < days)
			{
				if (IsBusinessDay(date)) {
					ctr++;
				}
				date = IncreaseDateByOne(date);
			}

			return date;

		}

		int main() {

			cout << "\nEnter Date1 : ";
			sDate Date1 = ReadFullDate();
			cout << "\nEnter Date2 : ";
			sDate Date2 = ReadFullDate();

			cout << "\nCompare Result = " << CompareDates(Date1, Date2);

			return 0;
		}
	};
	class Problem57Review{
		struct sDate
		{
			int Year;
			int Month;
			int Day;
		};
		//sDate IncreaseDateByOne(sDate Date);

		enum enDateCompare { Before = -1, Equal = 0, After = 1 };

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

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		bool IsLastDayInMonth(sDate Date) {

			return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));

		}

		bool IsLastMonthInYear(int month) {

			return (month == 12);
		}

		bool IsFirstDayInMonth(sDate Date) {
			return Date.Day == 1;
		}

		bool IsFirstMonthInYear(int month) {
			return (month == 1);
		}

		bool IsDate1EqualDate2(sDate Date1, sDate Date2) {
			return(Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? (Date1.Day == Date2.Day) : false) : false;
		}

		bool IsDate1BeforeDate2(sDate Date1, sDate Date2)//
		{
			return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
				(Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ?
					Date1.Day < Date2.Day : false)) : false);
		}

		bool IsDate1AfterDate2(sDate Date1, sDate Date2)//
		{
			return (Date1.Year > Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
				(Date1.Month > Date2.Month ? true : (Date1.Month == Date2.Month ?
					Date1.Day > Date2.Day : false)) : false);
		}

		bool IsDate1AfterDate2CourseApproach(sDate date1, sDate date2) {//

			return (!IsDate1BeforeDate2(date1, date2) && !IsDate1EqualDate2(date1, date2));

		}

		enDateCompare CompareDates(sDate date1, sDate date2) {


			if (IsDate1BeforeDate2(date1, date2))
				return enDateCompare::Before;

			if (IsDate1EqualDate2(date1, date2))
				return enDateCompare::Equal;

			return enDateCompare::After;
		}

		void SwapDates(sDate& date1, sDate& date2) {

			sDate TempDate;

			TempDate.Year = date1.Year;
			TempDate.Month = date1.Month;
			TempDate.Day = date1.Day;

			date1.Year = date2.Year;
			date1.Month = date2.Month;
			date1.Day = date2.Day;

			date2.Year = TempDate.Year;
			date2.Month = TempDate.Month;
			date2.Day = TempDate.Day;
		}

		int GetDifferenceInDays(sDate date, sDate date1, bool IncludeEndDay = false) {

			int days = 0;
			short swapFlagValue = 1;

			if (!IsDate1BeforeDate2(date, date1)) {
				SwapDates(date, date1);
				swapFlagValue = -1;
			}

			while (IsDate1BeforeDate2(date, date1))
			{
				days++;
				date = IncreaseDateByOne(date);
			}

			return IncludeEndDay ? ++days * swapFlagValue : days * swapFlagValue;
		}

		sDate IncreaseDateByOne(sDate Date) {

			if (IsLastDayInMonth(Date)) {
				if (IsLastMonthInYear(Date.Month)) {
					Date.Month = 1;
					Date.Day = 1;
					Date.Year++;
				}
				else
				{
					Date.Day = 1;
					Date.Month++;
				}
			}
			else
			{
				Date.Day++;
			}

			return Date;
		}

		int CompareTwoDates(sDate date, sDate date1, bool flag = false) {

			int total1Days = 0;
			int total2Days = 0;

			for (int i = 1; i <= date.Month - 1; i++)
			{
				total1Days += NumberOfDaysInMonth(i, date.Year);
			}
			total1Days += date.Day;


			for (int i = 1; i <= date1.Month - 1; i++)
			{
				total2Days += NumberOfDaysInMonth(i, date1.Year);
			}
			total2Days += date1.Day;


			return flag ? (abs(total1Days - total2Days) + 1) : abs(total1Days - total2Days);

		}

		string GetDayName(int DayOfWeekOrder) {
			string names[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
			return names[DayOfWeekOrder];
		}

		int GetDayIndex(int year, int month, int day) {
			int a = (14 - month) / 12;
			int y = year - a;
			int m = month + 12 * a - 2;
			return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
		}

		void PrintMonthStat(sDate Date) {

			cout << "Today is " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		void StartVacation(sDate Date) {

			cout << "/nVacation From : " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		void EndOfvacation(sDate Date) {

			cout << "\nVacation To " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		sDate GetSystemDate() {

			sDate date;

			time_t t = time(0);
			tm* now = localtime(&t);

			date.Year = now->tm_year + 1900;
			date.Month = now->tm_mon + 1;
			date.Day = now->tm_mday;

			return date;
		}

		bool IsEndOfWeek(sDate Date) {

			int dayIndex = GetDayIndex(Date.Year, Date.Month, Date.Day);

			return (dayIndex == 6);

		}

		bool IsWeekEnd(sDate Date) {

			int dayIndex = GetDayIndex(Date.Year, Date.Month, Date.Day);

			return (dayIndex == 5 || dayIndex == 6);

		}

		bool IsBusinessDay(sDate Date) {
			return  !IsWeekEnd(Date);
		}

		int DaysUntilEndOfWeek(sDate date) {

			int indexOfDay = GetDayIndex(date.Year, date.Month, date.Day);

			return (7 - (indexOfDay + 1));

		}

		int DaysUntilEndOfMonth(sDate date) {

			int numOfDaysInMonth = NumberOfDaysInMonth(date.Month, date.Year);

			return (numOfDaysInMonth - date.Day);

		}

		int NumberOfDays(int year) {
			return IsLeapYear(year) ? 366 : 365;
		}

		int DaysUntilEndOfYear(sDate Date) {

			int totalDays = PrintTotalDaysFromTheBeginningOfYear(Date.Year, Date.Month, Date.Day);

			return (NumberOfDays(Date.Year) - totalDays);

		}

		int GetActualVacationDays(sDate startDate, sDate endDate) {

			int ctr = 0;

			while (IsDate1BeforeDate2(startDate, endDate))
			{
				if (IsBusinessDay(startDate)) {
					ctr++;
				}
				startDate = IncreaseDateByOne(startDate);
			}
			return ctr;
		}

		sDate GetDayToReturnToWorks(int days, sDate date) {

			int ctr = 0;
			while (ctr < days)
			{
				if (IsBusinessDay(date)) {
					ctr++;
				}
				date = IncreaseDateByOne(date);
			}

			return date;

		}

		bool OverlapTwoPeriods(sDate startDate1, sDate endDate1, sDate startDate2, sDate endDate2) {

			if (CompareDates(startDate1, endDate1) == enDateCompare::Before ||
				CompareDates(startDate2, endDate2) == enDateCompare::After)
				return false;
			else
				return true;
		}

		int main() {

			//cout << "First Periods : " << endl;;

			//cout << "\nEnter Start Date1 : ";
			//sDate startDate = ReadFullDate();
			//cout << "\nEnter End Date1 : ";
			//sDate endDate1 = ReadFullDate();

			//cout << "\nEnter Start Date2 : ";
			//sDate startDate = ReadFullDate();
			//cout << "\nEnter End Date2 : ";
			//sDate endDate1 = ReadFullDate();




			return 0;
		}
	};
	class Problem58 {
		struct sDate
		{
			int Year;
			int Month;
			int Day;
		};
		sDate IncreaseDateByOne(sDate Date);

		enum enDateCompare { Before = -1, Equal = 0, After = 1 };

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

		sDate ReadFullDate() {
			sDate Date;

			Date.Day = ReadNumber("\nPlease enter a Day : ");
			Date.Month = ReadNumber("\nPlease enter a Month : ");
			Date.Year = ReadNumber("\nPlease enter a Year : ");

			return Date;
		}

		bool IsLastDayInMonth(sDate Date) {

			return (Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year));

		}

		bool IsLastMonthInYear(int month) {

			return (month == 12);
		}

		bool IsFirstDayInMonth(sDate Date) {
			return Date.Day == 1;
		}

		bool IsFirstMonthInYear(int month) {
			return (month == 1);
		}

		bool IsDate1EqualDate2(sDate Date1, sDate Date2) {
			return(Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? (Date1.Day == Date2.Day) : false) : false;
		}

		bool IsDate1BeforeDate2(sDate Date1, sDate Date2)//
		{
			return  (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
				(Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ?
					Date1.Day < Date2.Day : false)) : false);
		}

		bool IsDate1AfterDate2(sDate Date1, sDate Date2)//
		{
			return (Date1.Year > Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
				(Date1.Month > Date2.Month ? true : (Date1.Month == Date2.Month ?
					Date1.Day > Date2.Day : false)) : false);
		}

		bool IsDate1AfterDate2CourseApproach(sDate date1, sDate date2) {//

			return (!IsDate1BeforeDate2(date1, date2) && !IsDate1EqualDate2(date1, date2));

		}

		enDateCompare CompareDates(sDate date1, sDate date2) {


			if (IsDate1BeforeDate2(date1, date2))
				return enDateCompare::Before;

			if (IsDate1EqualDate2(date1, date2))
				return enDateCompare::Equal;

			return enDateCompare::After;
		}

		void SwapDates(sDate& date1, sDate& date2) {

			sDate TempDate;

			TempDate.Year = date1.Year;
			TempDate.Month = date1.Month;
			TempDate.Day = date1.Day;

			date1.Year = date2.Year;
			date1.Month = date2.Month;
			date1.Day = date2.Day;

			date2.Year = TempDate.Year;
			date2.Month = TempDate.Month;
			date2.Day = TempDate.Day;
		}

		int GetDifferenceInDays(sDate date, sDate date1, bool IncludeEndDay = false) {

			int days = 0;
			short swapFlagValue = 1;

			if (!IsDate1BeforeDate2(date, date1)) {
				SwapDates(date, date1);
				swapFlagValue = -1;
			}

			while (IsDate1BeforeDate2(date, date1))
			{
				days++;
				date = IncreaseDateByOne(date);
			}

			return IncludeEndDay ? ++days * swapFlagValue : days * swapFlagValue;
		}

		sDate IncreaseDateByOne(sDate Date) {

			if (IsLastDayInMonth(Date)) {
				if (IsLastMonthInYear(Date.Month)) {
					Date.Month = 1;
					Date.Day = 1;
					Date.Year++;
				}
				else
				{
					Date.Day = 1;
					Date.Month++;
				}
			}
			else
			{
				Date.Day++;
			}

			return Date;
		}

		int CompareTwoDates(sDate date, sDate date1, bool flag = false) {

			int total1Days = 0;
			int total2Days = 0;

			for (int i = 1; i <= date.Month - 1; i++)
			{
				total1Days += NumberOfDaysInMonth(i, date.Year);
			}
			total1Days += date.Day;


			for (int i = 1; i <= date1.Month - 1; i++)
			{
				total2Days += NumberOfDaysInMonth(i, date1.Year);
			}
			total2Days += date1.Day;


			return flag ? (abs(total1Days - total2Days) + 1) : abs(total1Days - total2Days);

		}

		string GetDayName(int DayOfWeekOrder) {
			string names[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
			return names[DayOfWeekOrder];
		}

		int GetDayIndex(int year, int month, int day) {
			int a = (14 - month) / 12;
			int y = year - a;
			int m = month + 12 * a - 2;
			return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
		}

		void PrintMonthStat(sDate Date) {

			cout << "Today is " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		void StartVacation(sDate Date) {

			cout << "/nVacation From : " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		void EndOfvacation(sDate Date) {

			cout << "\nVacation To " << GetDayName(GetDayIndex(Date.Year, Date.Month, Date.Day))
				<< " , " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
		}

		sDate GetSystemDate() {

			sDate date;

			time_t t = time(0);
			tm* now = localtime(&t);

			date.Year = now->tm_year + 1900;
			date.Month = now->tm_mon + 1;
			date.Day = now->tm_mday;

			return date;
		}

		bool IsEndOfWeek(sDate Date) {

			int dayIndex = GetDayIndex(Date.Year, Date.Month, Date.Day);

			return (dayIndex == 6);

		}

		bool IsWeekEnd(sDate Date) {

			int dayIndex = GetDayIndex(Date.Year, Date.Month, Date.Day);

			return (dayIndex == 5 || dayIndex == 6);

		}

		bool IsBusinessDay(sDate Date) {
			return  !IsWeekEnd(Date);
		}

		int DaysUntilEndOfWeek(sDate date) {

			int indexOfDay = GetDayIndex(date.Year, date.Month, date.Day);

			return (7 - (indexOfDay + 1));

		}

		int DaysUntilEndOfMonth(sDate date) {

			int numOfDaysInMonth = NumberOfDaysInMonth(date.Month, date.Year);

			return (numOfDaysInMonth - date.Day);

		}

		int NumberOfDays(int year) {
			return IsLeapYear(year) ? 366 : 365;
		}

		int DaysUntilEndOfYear(sDate Date) {

			int totalDays = PrintTotalDaysFromTheBeginningOfYear(Date.Year, Date.Month, Date.Day);

			return (NumberOfDays(Date.Year) - totalDays);

		}

		int GetActualVacationDays(sDate startDate, sDate endDate) {

			int ctr = 0;

			while (IsDate1BeforeDate2(startDate, endDate))
			{
				if (IsBusinessDay(startDate)) {
					ctr++;
				}
				startDate = IncreaseDateByOne(startDate);
			}
			return ctr;
		}

		sDate GetDayToReturnToWorks(int days, sDate date) {

			int ctr = 0;
			while (ctr < days)
			{
				if (IsBusinessDay(date)) {
					ctr++;
				}
				date = IncreaseDateByOne(date);
			}

			return date;

		}

		bool OverlapTwoPeriods(sDate startDate1, sDate endDate1, sDate startDate2, sDate endDate2) {

			if (CompareDates(startDate1, endDate1) == enDateCompare::Before ||
				CompareDates(startDate2, endDate2) == enDateCompare::After)
				return false;
			else
				return true;
		}

		int PeriodLengthInDays(sDate startDate, sDate endDate, bool IncludeEndDate = false) {
			return GetDifferenceInDays(startDate, endDate, IncludeEndDate);
		}

		int main() {

			cout << "First Periods : " << endl;;

			cout << "\nEnter Start Date1 : ";
			sDate startDate1 = ReadFullDate();
			cout << "\nEnter End Date1 : ";
			sDate endDate1 = ReadFullDate();

			cout << "\nPeriod Length is : " << PeriodLengthInDays(startDate1, endDate1);
			cout << "\nPeriod Length (Including End Date) is : " << PeriodLengthInDays(startDate1, endDate1, true);

			return 0;
		}
	};
}
