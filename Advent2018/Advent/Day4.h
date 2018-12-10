#pragma once

#include "DateTime.h"

class Day4 
{
public:

	static void Solve();

private:

	struct GuardAction {
		int guardId;
		DateTime dateTime;
		string action;

		GuardAction(int guardId, DateTime dateTime, string action) {
			this->guardId = guardId;
			this->dateTime = dateTime;
			this->action = action;
		}

		GuardAction() : guardId(0), dateTime(DateTime()), action("") {};
	};

	struct Guard {
		int guardId;
		vector<int> asleep;

		Guard(int guardId) {
			this->guardId = guardId;
			this->asleep.resize(60, 0);
		}

		Guard() : guardId(0) {};

		// Result is incremental on current values
		void SetAsleepTime(int from, int to) {
			for (int i = from; i < to; i++)
				asleep[i]++;
		}
	};
};