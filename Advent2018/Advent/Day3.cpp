#include "Day3.h"
#include "Helper.h"

#include <iostream>
#include <vector>
#include <string>
#include <regex>

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

	for (auto& line : data) {
		cout << line << endl;
		if (regex_match(line, base_match, base_regex))
		{
			auto& number = base_match[1]; // number
			auto& x = base_match[2];
			auto& y = base_match[3];
			auto& widthX = base_match[4];
			auto& widthY = base_match[5];

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