#include "advent2018.h"
#include "FileHelper.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <regex>
#include <map>

/*
https://adventofcode.com/2018/day/3
*/

static void part1();
static void part2();

void day03(input_t input)
{
	part1();
	part2();
}

void part1()
{
	std::cout << "Day3 part 1" << std::endl;

	std::vector<std::string> data = FileHelper::ReadFileToStringVector("./input/day03.txt");

	std::regex base_regex("#(\\d+)...(\\d+),(\\d+):.(\\d+)x(\\d+)");
	std::smatch base_match;

	std::map<int, std::map<int, int>> fabricClaims;
	for (auto& line : data) {
		if (regex_match(line, base_match, base_regex))
		{
			int dataX = stoi(base_match[2]);
			int dataY = stoi(base_match[3]);
			int maxX = dataX + stoi(base_match[4]);
			int maxY = dataY + stoi(base_match[5]);

			for (int x = dataX; x < maxX; x++) {
				auto it = fabricClaims.find(x);

				if (it == fabricClaims.end())
					fabricClaims.insert(std::make_pair(x, std::map<int, int>()));

				std::map<int, int>& row = fabricClaims.at(x);
				for (int y = dataY; y < maxY; y++) {

					auto rowIt = row.find(y);
					if (rowIt == row.end())
						row.insert(std::make_pair(y, 1));
					else
						rowIt->second += 1;
				}
			}
		}
	}
	
	int count = 0;

	for (auto const& x : fabricClaims) {
		for (auto const& y : x.second) {
			if (y.second >= 2)
				count++;
		}
	}

	std::cout << "Answer: " << count << std::endl;
}

void part2()
{
	std::cout << "Day3 part 2" << std::endl;

	std::vector<std::string> data = FileHelper::ReadFileToStringVector("./input/day03.txt");

	std::regex base_regex("#(\\d+)...(\\d+),(\\d+):.(\\d+)x(\\d+)");
	std::smatch base_match;

	std::map<int, bool> numberHasOverlap;

	std::map<int, std::map<int, std::vector<int>>> fabricClaims;
	for (auto& line : data) {
		if (regex_match(line, base_match, base_regex)) {
			int number = stoi(base_match[1]);
			int dataX = stoi(base_match[2]);
			int dataY = stoi(base_match[3]);
			int maxX = dataX + stoi(base_match[4]);
			int maxY = dataY + stoi(base_match[5]);

			for (int x = dataX; x < maxX; x++) {
				if (fabricClaims.find(x) == fabricClaims.end())
					fabricClaims.insert(std::make_pair(x, std::map<int, std::vector<int>>()));

				std::map<int, std::vector<int>>& row = fabricClaims.at(x);
				for (int y = dataY; y < maxY; y++) {
					if (row.find(y) == row.end())
						row.insert(std::make_pair(y, std::vector<int>()));
	
					if (numberHasOverlap.find(number) == numberHasOverlap.end())
						numberHasOverlap.insert(std::make_pair(number, false));

					std::vector<int>& column = row.at(y);
					column.push_back(number);

					if (column.size() > 1) {
						for (auto& value : column) {
							numberHasOverlap.find(value)->second = true;
						}
					}
				}
			}
		}
	}

	for (auto& number : numberHasOverlap) {
		if (!number.second)
			std::cout << "Answer: " << number.first << std::endl;
	}
}