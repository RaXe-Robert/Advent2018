#include "advent2018.h"
#include "FileHelper.h"

#include <iostream>
#include <string>
#include <locale>

static size_t solvePolymer(std::string polymer);
static std::string excludeCharacter(std::string polymer, char character);

void day05(const char* filepath)
{
	std::string polymer = FileHelper::ReadFileToStringVector(filepath)[0];
	std::vector<char> characters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	auto result = solvePolymer(polymer);
	printf("(Part 1) Answer: %zu\n", result);

	size_t smallestResult = result;
	char bestCharacter;
	for (auto& character : characters) {
		std::string modifiedPolymer = excludeCharacter(polymer, character);
		result = solvePolymer(modifiedPolymer);

		if (result <= smallestResult) {
			smallestResult = result;
			bestCharacter = character;
		}

		printf("(Part2) %c, result: %zu\n", character, result);
	}

	printf("(Part2) Answer: %c, with: %zu\n", bestCharacter, smallestResult);
}

size_t solvePolymer(std::string polymer)
{
	std::locale loc;

	bool noMoreOccurencess = false;
	while (!noMoreOccurencess) {
		bool stop = true;
		for (size_t i = polymer.size() - 2; i >= 0; i--) {
			// Check if same character
			if (tolower(polymer[i], loc) != tolower(polymer[i + 1], loc))
				continue;

			if ((isupper(polymer[i]) && islower(polymer[i + 1]))
				|| (islower(polymer[i]) && isupper(polymer[i + 1]))) {
				polymer.erase(i, 2);
				stop = false;
			}
		}
		noMoreOccurencess = stop;
	}

	return polymer.size();
}

std::string excludeCharacter(std::string polymer, char character)
{
	std::locale loc;

	for (size_t i = polymer.size() - 1; i >= 0; i--) {
		if (tolower(polymer[i], loc) == character)
			polymer.erase(i, 1);
	}

	return polymer;
}