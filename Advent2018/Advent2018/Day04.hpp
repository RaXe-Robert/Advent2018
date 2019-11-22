/*
https://adventofcode.com/2018/day/4
*/

struct GuardAction 
{
	s32 guardId;
	DateTime dateTime;
	const char* action;

	GuardAction(s32 guardId, DateTime dateTime, const char* action) 
	{
		this->guardId = guardId;
		this->dateTime = dateTime;
		this->action = action;
	}
};

struct Guard 
{
	s32 id;
	std::vector<s32> asleep;

	Guard(s32 guardId) 
	{
		this->id = guardId;
		this->asleep.resize(60, 0);
	}

	Guard() : id(0) {};

	void setAsleepTime(int from, int to)
	{
		for (int i = from; i < to; i++)
			asleep[i]++;
	}
};

void day04(const char* filepath)
{
	std::vector<char*> data = ReadFileToStringVector(filepath);

	std::regex dateTime_regex("\\[(\\d+)\\-(\\d+)\\-(\\d+) (\\d+)\\:(\\d+)\\] (.*)");
	std::regex guard_regex("(\\w+) \\#(\\d+)");

	std::vector<GuardAction> guardActions;

	std::cmatch match;
	for (auto line : data) {
		if (!std::regex_search(line, match, dateTime_regex))
			continue;

		int year = stoi(match[1]);
		int month = stoi(match[2]);
		int day = stoi(match[3]);
		int hour = stoi(match[4]);
		int minute = stoi(match[5]);

		auto str = match[6].str();

		char* action = new char[str.size() + 1];
		std::copy(str.begin(), str.end(), action);
		action[str.size()] = '\0';

		auto dateTime = new DateTime;
		dateTime->year = year;
		dateTime->month = month;
		dateTime->day = day;
		dateTime->hour = hour;
		dateTime->minute = minute;

		std::cmatch guard_match;
		if (std::regex_search(action, guard_match, guard_regex)) {
			auto guardId = stoi(guard_match[2]);
			auto guardAction = new GuardAction(guardId, *dateTime, "begins shift");

			guardActions.push_back(*guardAction);
		}
		else {
			auto guardId = -1;
			auto guardAction = new GuardAction(guardId, *dateTime, action);

			guardActions.push_back(*guardAction);
		}
	}

	sort(guardActions.begin(), guardActions.end(), [](GuardAction i, GuardAction j) {
		return SmallerOrEqual(i.dateTime, j.dateTime);
	});

	std::map<s32, Guard> guardsMap;
	s32 currentGuard;
	s32 startedSleeping;
	for (auto guardAction : guardActions) 
	{ 
		if (guardAction.guardId != -1) 
		{
			if (guardsMap.find(guardAction.guardId) == guardsMap.end()) 
			{
				auto guard = new Guard(guardAction.guardId);
				auto pair = std::make_pair(guardAction.guardId, *guard);
				guardsMap.insert(pair);
			}

			currentGuard = guardAction.guardId;
		}
		else 
		{
			if (strcmp(guardAction.action, "falls asleep") == 0)
				startedSleeping = guardAction.dateTime.minute;
			else if (strcmp(guardAction.action, "wakes up") == 0)
			{
				auto it = guardsMap.find(currentGuard);
				if (it != guardsMap.end())
				{
					it->second.setAsleepTime(startedSleeping, guardAction.dateTime.minute);
				}
				else
					printf("Failed - sorting probably went wrong\n");
			}
		}
	}

	Guard longestSleeper;
	s32 longestSleepTime = 0;
	s32 longestMinute = -1;
	for (auto guardEntry : guardsMap) 
	{
		auto guard = guardEntry.second;

		s32 sum = 0;
		s32 currLongestMinute = 0;

		for (size_t i = 0; i < guard.asleep.size(); i++)
		{
			sum += guard.asleep[i];
			if (guard.asleep[i] > guard.asleep[currLongestMinute])
				currLongestMinute = i;
		}

		if (sum > longestSleepTime) {
			longestSleepTime = sum;
			longestSleeper = guard;
			longestMinute = currLongestMinute;
		}
	}

	printf("[Day04][1] Answer: %i, Guard ID: %i, Longest minute: %i\n", longestSleeper.id * longestMinute, longestSleeper.id, longestMinute);

	Guard sleptLongestOnMinute;
	int biggestDifference = 0;
	int indexOfBiggestDifference = 0;
	for (int i = 0; i < 60; i++) 
	{
		int indexOfSecondHighest = -1;
		int idOfHighest = -1;
		
		for (auto guardEntry : guardsMap) 
		{
			auto guard = guardEntry.second;

			if (idOfHighest == -1 || guardEntry.second.asleep[i] >= guardsMap.find(idOfHighest)->second.asleep[i])
			{
				indexOfSecondHighest = idOfHighest;
				idOfHighest = guardEntry.second.id;
			}
		}

		Guard highest = guardsMap.find(idOfHighest)->second;
		Guard secondHighest = guardsMap.find(indexOfSecondHighest)->second;

		int difference = highest.asleep[i] - secondHighest.asleep[i];
		if (difference >= biggestDifference) 
		{
			sleptLongestOnMinute = idOfHighest;
			biggestDifference = difference;
			indexOfBiggestDifference = i;
		}
	}

	printf("[Day04][2] Answer: %i, Guard ID: %i, Longest minute: %i\n", sleptLongestOnMinute.id * indexOfBiggestDifference, sleptLongestOnMinute.id, indexOfBiggestDifference);
}