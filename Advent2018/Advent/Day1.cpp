#include "Day1.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

/*
https://adventofcode.com/2018/day/1
*/

void Day1::Solve()
{
	cout << "Day1 part 2" << endl;

	vector<int> numbers = { 0 };

	bool foundPair = false;
	int currentFrequency = 0;

	int amountOfLoops = 0;

	while (!foundPair) {

		ifstream inFile("D:\\input.txt");

		if (!inFile) {
			cerr << "Unable to open file input.txt" << endl;
			exit(1);
		}

		cout << "STARTING LOOP: " << ++amountOfLoops << endl;
		int x;

		while (inFile >> x && !foundPair) {

			int newFrequency = currentFrequency + x;

			vector<int>::iterator it = find(numbers.begin(), numbers.end(), newFrequency);
			if (it != numbers.end()) {
				cout << "MATCH: " << newFrequency << endl;
				foundPair = true;
			}

			numbers.push_back(newFrequency);
			currentFrequency = newFrequency;
		}

		inFile.close();
	}
}