#include "DateTime.h"

using namespace std;

DateTime::DateTime()
{
	this->year = 0;
	this->month = 0;
	this->day = 0;
	this->hour = 0;
	this->minute = 0;
}

DateTime::DateTime(int year, int month, int day, int hour, int minute) 
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
}


// Compares this dateTime to the given value and returns the difference (can be negative values)
DateTime DateTime::Compare(DateTime dateTime) 
{
	return DateTime(
		this->year - dateTime.year,
		this->month - dateTime.month,
		this->day - dateTime.day,
		this->hour - dateTime.hour,
		this->minute - dateTime.minute
	);

}

const int DateTime::Year()
{
	return this->year;
}

const int DateTime::Month()
{
	return this->month;
}
const int DateTime::Day()
{
	return this->day;
}

const int DateTime::Hour()
{
	return this->hour;
}

const int DateTime::Minute()
{
	return this->minute;
}