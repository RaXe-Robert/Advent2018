#pragma once

#include <vector>
#include <string>

using namespace std;

class DateTime
{
	public:
		DateTime();
		DateTime(int year, int month, int day, int hour, int minute);

		DateTime Compare(DateTime dateTime);

		const int Year();
		const int Month();
		const int Day();
		const int Hour();
		const int Minute();

		bool operator==(const DateTime& toCompare) {
			return this->AreEqual(toCompare);
		}

		bool operator<=(const DateTime& toCompare) {
			if (this->AreEqual(toCompare))
				return true;

			if (this->year != toCompare.year)
				return this->year < toCompare.year;

			if (this->month != toCompare.month)
				return this->month < toCompare.month;

			if (this->day != toCompare.day)
				return this->day < toCompare.day;

			if (this->hour != toCompare.hour)
				return this->hour < toCompare.hour;

			return this->minute < toCompare.minute;
		}

	private:
		int year;
		int month;
		int day;
		int hour;
		int minute;

		bool AreEqual(const DateTime& toCompare) {
			return (this->year == toCompare.year
				&& this->month == toCompare.month
				&& this->day == toCompare.day
				&& this->hour == toCompare.hour
				&& this->minute == toCompare.minute
				);
		}
};