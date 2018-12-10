#include "Day4.h"
#include "FileHelper.h"
#include "DateTime.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <regex>
#include <map>
#include <chrono>

using namespace std;

/*
https://adventofcode.com/2018/day/4
*/

void Day4::Solve()
{
	cout << "Day4 part 1" << endl;

	vector<string> data = FileHelper::ReadFileToStringVector("D:\\input4.txt");

	regex dateTime_regex("\\[(\\d+)\\-(\\d+)\\-(\\d+) (\\d+)\\:(\\d+)\\] (.*)");
	regex guard_regex("(\\w+) \\#(\\d+)");

	vector<GuardAction> guardActions;

	smatch base_match;
	for (auto& line : data) {
		if (!regex_search(line, base_match, dateTime_regex))
			continue;

		int year = stoi(base_match[1]);
		int month = stoi(base_match[2]);
		int day = stoi(base_match[3]);
		int hour = stoi(base_match[4]);
		int minute = stoi(base_match[5]);
		string action = base_match[6];

		smatch guard_match;
		if (regex_search(action, guard_match, guard_regex))
			guardActions.push_back(GuardAction(stoi(guard_match[2]), DateTime(year, month, day, hour, minute), "begins shift"));
		else
			guardActions.push_back(GuardAction(-1, DateTime(year, month, day, hour, minute), action));
	}

	sort(guardActions.begin(), guardActions.end(), [](GuardAction i, GuardAction j) {
		return i.dateTime <= j.dateTime;
	});

	map<int, Guard> guards;
	int currentGuard;
	int startedSleeping;
	for (auto& x : guardActions) {
		if (x.guardId != -1) {
			if (guards.find(x.guardId) == guards.end())
				guards.insert(make_pair(x.guardId, Guard(x.guardId)));

			currentGuard = x.guardId;
		}
		else {
			if (x.action == "falls asleep")
				startedSleeping = x.dateTime.Minute();
			else if (x.action == "wakes up") {
				auto it = guards.find(currentGuard);
				if (it != guards.end())
					it->second.SetAsleepTime(startedSleeping, x.dateTime.Minute());
				else
					cout << "Failed - sorting probably went wrong" << endl;
			}
		}
	}

	Guard longestSleeper;
	int longestSleepTime = 0;
	int longestMinute;
	for (auto& guard : guards) {
		int sum = 0;
		int currLongestMinute = 0;

		for (int i = 0; i < guard.second.asleep.size(); i++) {
			sum += guard.second.asleep[i];
			if (guard.second.asleep[i] > guard.second.asleep[currLongestMinute])
				currLongestMinute = i;
		}
		if (sum > longestSleepTime) {
			longestSleepTime = sum;
			longestSleeper = guard.second;
			longestMinute = currLongestMinute;
		}
	}

	cout << "(Part1) Answer: " << longestSleeper.guardId * longestMinute << ", Guard ID: " << longestSleeper.guardId << ", Longest minute: " << longestMinute << endl;

	Guard sleptLongestOnMinute;
	int biggestDifference = 0;
	int indexOfBiggestDifference = 0;
	for (int i = 0; i < 60; i++) {		
		int indexOfSecondHighest = -1;
		int idOfHighest = -1;
		
		for (auto& guard : guards) {
			if (idOfHighest == -1 || guard.second.asleep[i] >= guards.at(idOfHighest).asleep[i]) {
				indexOfSecondHighest = idOfHighest;
				idOfHighest = guard.second.guardId;
			}
		}

		int difference = guards.at(idOfHighest).asleep[i] - guards.at(indexOfSecondHighest).asleep[i];
		if (difference >= biggestDifference) {
			sleptLongestOnMinute = idOfHighest;
			biggestDifference = difference;
			indexOfBiggestDifference = i;
		}
	}

	cout << "(Part2) Answer: " << sleptLongestOnMinute.guardId * indexOfBiggestDifference << ", Guard ID: " << sleptLongestOnMinute.guardId << ", Longest minute: " << indexOfBiggestDifference << endl;
}