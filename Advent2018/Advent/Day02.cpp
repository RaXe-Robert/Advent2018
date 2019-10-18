#include "advent2018.h"
#include "FileHelper.h"

#include <vector>
#include <iostream>
#include <map>
#include <string>

using namespace std;

/*
https://adventofcode.com/2018/day/2
*/

static void part1();
static void part2();

void day02(input_t input)
{
	part1();
	part2();
}

void part1()
{
	cout << "Day2 part 1" << endl;
		
	vector<string> data = FileHelper::ReadFileToStringVector("./input/day02.txt");

	int doubleCounter = 0;
	int tripleCounter = 0;

	for (auto& line : data) {

		cout << line << endl;

		map<char, int> charOccurrences;

		for (auto& x : line) {
			auto iterator = charOccurrences.find(x);
			if (iterator != charOccurrences.end()) {
				charOccurrences[x] += 1;
			}
			else {
				charOccurrences.insert(make_pair(x, 1));
			}
		}

		bool countedDouble = false;
		bool countedTriple = false;

		map<char, int>::iterator it;
		for (it = charOccurrences.begin(); it != charOccurrences.end(); it++)
		{
			if (it->second == 2 && !countedDouble) {
				doubleCounter++;
				countedDouble = true;
			}

			if (it->second == 3 && !countedTriple) {
				tripleCounter++;
				countedTriple = true;
			}
		}
	}

	cout << "Answer: " << doubleCounter * tripleCounter << endl;
}

void part2()
{
	cout << "Day2 part 2" << endl;

	vector<string> data = FileHelper::ReadFileToStringVector("./input/day02.txt");

	for (size_t x = 0; x != data.size(); ++x) {
		// Compare against all other strings, except for itself
		for (size_t y = 0; y != data.size(); ++y) {
			if (x == y)
				continue;

			int differenceCount = 0;
			string result = "";

			// Compare characters
			for (int i = 0; i < data[x].size(); i++) {
				if (data[x][i] != data[y][i])
					differenceCount++;
				else
					result += data[x][i];

				if (differenceCount > 1)
					break;
			}

			if (differenceCount == 1) {
				cout << "Answer: " << result << endl;
				return;
			}
		}
	}
}