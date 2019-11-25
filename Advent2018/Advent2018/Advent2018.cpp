#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <time.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <regex>

#define CRASH *(int*)0=0
#define assert(expr) if (!(expr)) { fprintf(stderr, "FAILED assertion [" __FILE__ ":%i] " #expr "\n", __LINE__);  CRASH; }

#include "shared/types.h"
#include "shared/dateTime.hpp"

#include "day01.hpp"
#include "day02.hpp"
#include "day03.hpp"
#include "day04.hpp"
#include "day05.hpp"
#include "day06.hpp"
#include "day07.hpp"

int main()
{
	printf("Advent of Code 2018\n\n");

	day01("./input/day01.txt");
	day02("./input/day02.txt");
	day03("./input/day03.txt");
	day04("./input/day04.txt");
	day05("./input/day05.txt");
	day06("./input/day06.txt");
	day07("./input/day07.txt");

	return 0;
}

/*
	auto m = malloc(1024);
	memset(m, 255, 1024);

	DateTime* dt = new (m) DateTime;
	printf("%u\n", dt->u[24]);
	*/
