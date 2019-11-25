/*
https://adventofcode.com/2018/day/4
*/

constexpr s32 MINUTES_PER_HOUR = 60;

struct GuardAction 
{
	s32 guardId;
	DateTime dateTime;
	const char* action;
};

struct Guard 
{
	s32 id;
	std::vector<s32> asleep;

	Guard(s32 guardId) 
	{
		this->id = guardId;
		this->asleep.resize(MINUTES_PER_HOUR, 0);
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
	std::regex dateTime_regex("\\[(\\d+)\\-(\\d+)\\-(\\d+) (\\d+)\\:(\\d+)\\] (.*)");
	std::cmatch match;

	std::regex guard_regex("(\\w+) \\#(\\d+)");
	std::cmatch guard_match;

	std::vector<GuardAction> guardActions;

	auto file = fopen(filepath, "rb");
	auto buffer = reinterpret_cast<char*>(malloc(128));

	for (auto i = 0; fgets(buffer, 128, file); i++) 
	{
		if (!std::regex_search(buffer, match, dateTime_regex))
			continue;
		
		auto dateTime = new DateTime;
		dateTime->year = stoi(match[1]);
		dateTime->month = stoi(match[2]);
		dateTime->day = stoi(match[3]);
		dateTime->hour = stoi(match[4]);
		dateTime->minute = stoi(match[5]);

		auto guardAction = new GuardAction;
		guardAction->dateTime = *dateTime;

		auto str = match[6].str();
		char* action = new char[str.size() + 1];
		std::copy(str.begin(), str.end(), action);
		action[str.size()] = '\0';

		if (std::regex_search(action, guard_match, guard_regex)) 
		{
			guardAction->guardId = stoi(guard_match[2]);
			guardAction->action = "begins shift";
		}
		else 
		{
			guardAction->guardId = -1;
			guardAction->action = action;
		}

		guardActions.push_back(*guardAction);
	}

	fclose(file);
	free(buffer);

	sort(guardActions.begin(), guardActions.end(), [](GuardAction i, GuardAction j) 
	{
		return smallerOrEqual(i.dateTime, j.dateTime);
	});

	std::map<s32, Guard> guardsMap;
	Guard* currentGuard = NULL;
	s32 startedSleeping = 0;
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

			currentGuard = &guardsMap.at(guardAction.guardId);
		}
		else 
		{
			if (strcmp(guardAction.action, "falls asleep") == 0)
				startedSleeping = guardAction.dateTime.minute;
			else if (strcmp(guardAction.action, "wakes up") == 0 && currentGuard != NULL)
				currentGuard->setAsleepTime(startedSleeping, guardAction.dateTime.minute);
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

		for (auto i = 0; i < MINUTES_PER_HOUR; i++)
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
	s32 biggestDifference = 0;
	s32 indexOfBiggestDifference = 0;

	for (auto i = 0; i < MINUTES_PER_HOUR; i++)
	{
		Guard highest = NULL;
		Guard secondHighest = NULL;
		
		for (auto guardEntry : guardsMap) 
		{
			auto guard = guardEntry.second;
			if (&highest == NULL || guard.asleep[i] >= highest.asleep[i])
			{
				secondHighest = highest;
				highest = guard;
			}
		}

		s32 difference = highest.asleep[i] - secondHighest.asleep[i];
		if (difference >= biggestDifference) 
		{
			sleptLongestOnMinute = highest;
			biggestDifference = difference;
			indexOfBiggestDifference = i;
		}
	}

	printf("[_____][2] Answer: %i, Guard ID: %i, Longest minute: %i\n", sleptLongestOnMinute.id * indexOfBiggestDifference, sleptLongestOnMinute.id, indexOfBiggestDifference);
}