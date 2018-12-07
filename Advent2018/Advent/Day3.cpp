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
		cout << line << endl;
		if (regex_match(line, base_match, base_regex))
		{
			int number = stoi(base_match[1]); // number
			int dataX = stoi(base_match[2]);
			int dataY = stoi(base_match[3]);
			int widthX = stoi(base_match[4]);
			int widthY = stoi(base_match[5]);

			for (int x = dataX; x < dataX + widthX; x++) {
				auto it = fabricClaims.find(x);

				if (it == fabricClaims.end())
					fabricClaims.insert(make_pair(x, map<int, int>()));

				map<int, int> row = fabricClaims.at(x);
				for (int y = dataY; y < dataY + widthY; y++) {
					auto rowIt = row.find(y);
					if (rowIt == row.end()) {
						row.insert(make_pair(y, 1));
					}
					else {
						rowIt->second += 1;
					}

				}
			}
		}
		else
			cout << "oops" << endl;
	}
}

void Day3::Part2()
{
	cout << "Day3 part 2" << endl;

	vector<string> data = Helper::ReadFileToStringVector("D:\\input3");
}