#include "advent2018.h"

#include "FileHelper.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <set>

/*
https://adventofcode.com/2018/day/1
*/

void day01(const char* filepath)
{
	printf("[Day01][1]\n");

	auto file = fopen(filepath, "rb");
	assert(file);

	std::vector<int> data;
	char buffer[100];

	int part1 = 0;

	while (!feof(file))
	{
		char* line = fgets(buffer, 100, file);
		if (line == NULL)
			break;

		int val = atoi(line);
		part1 += val;
		data.push_back(val);
	}

	fclose(file);
	printf("[Day01][1] Answer: %i\n", part1);

	printf("[Day01][2]\n");

	std::set<int> set = { };
	int frequency = 0;

	while (true) {
		for (int i : data) {
			frequency += i;
			auto x = set.insert(frequency);
			if (!x.second) {
				printf("[Day01][2] Answer: %i\n", frequency);
				return;
			}
		}
	}
}
