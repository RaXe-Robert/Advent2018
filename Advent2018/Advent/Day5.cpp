#include "Day5.h"
#include "FileHelper.h"

#include <iostream>
#include <string>
#include <locale>

using namespace std;

void Day5::Solve()
{
	string polymer = FileHelper::ReadFileToString("D:\\input5.txt");
	vector<char> characters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	int result = SolvePolymer(polymer);
	cout << "(Part 1) Answer: " << result << endl;

	int smallestResult = result;
	char bestCharacter;
	for (auto& character : characters) {
		string modifiedPolymer = ExcludeCharacter(polymer, character);
		result = SolvePolymer(modifiedPolymer);

		if (result <= smallestResult) {
			smallestResult = result;
			bestCharacter = character;
		}

		cout << "(Part2) " << character << ", result: " << result << endl;
	}
	cout << "(Part2) Answer: " << bestCharacter << ", with: " << smallestResult << endl;
}

int Day5::SolvePolymer(string polymer)
{
	locale loc;

	bool noMoreOccurencess = false;
	while (!noMoreOccurencess) {
		bool stop = true;
		for (int i = polymer.size() - 2; i >= 0; i--) {
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

string Day5::ExcludeCharacter(string polymer, char character)
{
	locale loc;

	for (int i = polymer.size() - 1; i >= 0; i--) {
		if (tolower(polymer[i], loc) == character)
			polymer.erase(i, 1);
	}

	return polymer;
}