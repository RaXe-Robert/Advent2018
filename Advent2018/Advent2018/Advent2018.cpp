#include <stdio.h>
#include <chrono>
#include <time.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <regex>
#include <locale>

#define CRASH *(int*)0=0
#define assert(expr) if (!(expr)) { fprintf(stderr, "FAILED assertion [" __FILE__ ":%i] " #expr "\n", __LINE__);  CRASH; }

#include "FileHelper.hpp"
#include "DateTime.hpp"
#include "Day01.hpp"
#include "Day02.hpp"
#include "Day03.hpp"
#include "Day04.hpp"
#include "Day05.hpp"
#include "Day06.hpp"

int main()
{
	printf("Advent of Code 2018\n\n");

	day01("./input/day01.txt");
	day02("./input/day02.txt");
	day03("./input/day03.txt");
	day04("./input/day04.txt");
	day05("./input/day05.txt");
	day06("./input/day06.txt");

	return 0;
}
