#include "Day1.h"
#include "Helper.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

/*
https://adventofcode.com/2018/day/1
*/

void Day1::Part2()
{
	cout << "Day1 part 2" << endl;

	vector<int> data = Helper::ReadFileToIntVector("D:\\input.txt");

	vector<int> numbers = { 0 };

	bool foundPair = false;
	int currentFrequency = 0;

	int amountOfLoops = 0;

	while (!foundPair) {
		cout << "STARTING LOOP: " << ++amountOfLoops << endl;

		for (auto& x : data) {
			if (foundPair)
				break;

			int newFrequency = currentFrequency + x;

			vector<int>::iterator it = find(numbers.begin(), numbers.end(), newFrequency);
			if (it != numbers.end()) {
				cout << "MATCH: " << newFrequency << endl;
				foundPair = true;
			}

			numbers.push_back(newFrequency);
			currentFrequency = newFrequency;
		}
	}
}