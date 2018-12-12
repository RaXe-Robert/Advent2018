#pragma once

#include <string>

class Day5
{
public:

	static void Solve();

private:
	static int SolvePolymer(std::string polymer);
	static std::string ExcludeCharacter(std::string polymer, char character);
};