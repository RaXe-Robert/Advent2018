#pragma once

#include <vector>
#include <string>

using namespace std;

class Helper
{
	public:

	static vector<string> ReadFileToStringVector(string filepath);
	static vector<int> ReadFileToIntVector(string filepath);
};