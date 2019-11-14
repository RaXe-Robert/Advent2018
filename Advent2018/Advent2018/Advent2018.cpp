// Advent2018.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <chrono>
#include <time.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#define CRASH *(int*)0=0
#define assert(expr) if (!(expr)) { fprintf(stderr, "FAILED assertion [" __FILE__ ":%i] " #expr "\n", __LINE__);  CRASH; }

#include "FileHelper.hpp"
#include "Day02.hpp"

int main()
{
	printf("Hello\n");


	auto buffer = new char[1024 * 128];
	day02("./input/day02.txt", buffer);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
