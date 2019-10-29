#include "advent2018.h"

#include "FileHelper.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

/*
https://adventofcode.com/2018/day/1
*/

void day01(input_t input)
{
	std::cout << "Day1 part 2" << std::endl;

	std::vector<int> data = FileHelper::ReadFileToIntVector("./input/day01.txt");

	std::vector<int> numbers = { 0 };

	bool foundPair = false;
	int currentFrequency = 0;

	int amountOfLoops = 0;

	while (!foundPair) {
		std::cout << "STARTING LOOP: " << ++amountOfLoops << std::endl;

		for (auto& x : data) {
			if (foundPair)
				break;

			int newFrequency = currentFrequency + x;

			std::vector<int>::iterator it = find(numbers.begin(), numbers.end(), newFrequency);
			if (it != numbers.end()) {
				std::cout << "MATCH: " << newFrequency << std::endl;
				foundPair = true;
			}

			numbers.push_back(newFrequency);
			currentFrequency = newFrequency;
		}
	}
}