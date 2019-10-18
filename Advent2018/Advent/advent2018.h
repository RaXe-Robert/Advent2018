#ifndef _ADVENT2018_H
#define _ADVENT2018_H

#include <string>

struct input_t {
	char* s;
	std::size_t len;
};

struct advent_t {
	void (*fn)(input_t);
	std::string input_file;
};

void day01(input_t);
void day02(input_t);
void day03(input_t);
void day04(input_t);
void day05(input_t);

#endif