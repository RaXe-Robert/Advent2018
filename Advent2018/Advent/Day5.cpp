#include "Day5.h"
#include "FileHelper.h"

#include <iostream>
#include <string>
#include <locale>

using namespace std;

void Day5::Solve()
{
	string data = FileHelper::ReadFileToString("D:\\input5.txt");

	locale loc;

	bool noMoreOccurencess = false;
	while (!noMoreOccurencess) {
		bool stop = true;
		for (int i = data.size() - 2; i >= 0; i--) {
			// Check if same character
			if (tolower(data[i], loc) != tolower(data[i + 1], loc))
				continue;

			if ((isupper(data[i]) && islower(data[i + 1]))
				|| (islower(data[i]) && isupper(data[i + 1]))) {
				data.erase(i, 2);
				stop = false;
			}
		}
		noMoreOccurencess = stop;
	}

	cout << "Answer: " << data.size() << endl;
}