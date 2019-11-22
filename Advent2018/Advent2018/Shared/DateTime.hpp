inline bool
AreEqual(DateTime l, DateTime r) {
	return (l.year == r.year
		&& l.month == r.month
		&& l.day == r.day
		&& l.hour == r.hour
		&& l.minute == r.minute
		);
}

inline bool
SmallerOrEqual(DateTime l, DateTime r) {
	if (l.year != r.year)
		return l.year < r.year;

	if (l.month != r.month)
		return l.month < r.month;

	if (l.day != r.day)
		return l.day < r.day;

	if (l.hour != r.hour)
		return l.hour < r.hour;

	if (l.minute != r.minute)
		return l.minute < r.minute;

	return true;
}