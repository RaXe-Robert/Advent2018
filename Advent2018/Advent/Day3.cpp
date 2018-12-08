#include "Day3.h"
#include "Helper.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <regex>
#include <map>

using namespace std;

/*
https://adventofcode.com/2018/day/3
*/

void Day3::Part1()
{
	cout << "Day3 part 1" << endl;

	vector<string> data = Helper::ReadFileToStringVector("D:\\input3.txt");

	regex base_regex("#(\\d+)...(\\d+),(\\d+):.(\\d+)x(\\d+)");
	smatch base_match;

	map<int, map<int, int>> fabricClaims;
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
					fabricClaims.insert(make_pair(x, map<int, int>()));

				map<int, int>& row = fabricClaims.at(x);
				for (int y = dataY; y < maxY; y++) {

					auto rowIt = row.find(y);
					if (rowIt == row.end())
						row.insert(make_pair(y, 1));
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

	cout << "Answer: " << count << endl;
}

void Day3::Part2()
{
	cout << "Day3 part 2" << endl;

	vector<string> data = Helper::ReadFileToStringVector("D:\\input3.txt");

	regex base_regex("#(\\d+)...(\\d+),(\\d+):.(\\d+)x(\\d+)");
	smatch base_match;

	map<int, bool> numberHasOverlap;

	map<int, map<int, vector<int>>> fabricClaims;
	for (auto& line : data) {
		if (regex_match(line, base_match, base_regex)) {
			int number = stoi(base_match[1]);
			int dataX = stoi(base_match[2]);
			int dataY = stoi(base_match[3]);
			int maxX = dataX + stoi(base_match[4]);
			int maxY = dataY + stoi(base_match[5]);

			for (int x = dataX; x < maxX; x++) {
				if (fabricClaims.find(x) == fabricClaims.end())
					fabricClaims.insert(make_pair(x, map<int, vector<int>>()));

				map<int, vector<int>>& row = fabricClaims.at(x);
				for (int y = dataY; y < maxY; y++) {
					if (row.find(y) == row.end())
						row.insert(make_pair(y, vector<int>()));
	
					if (numberHasOverlap.find(number) == numberHasOverlap.end())
						numberHasOverlap.insert(make_pair(number, false));

					vector<int>& column = row.at(y);
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
			cout << "Answer: " << number.first << endl;
	}
}