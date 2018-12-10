#pragma once

#include <vector>
#include <string>

using namespace std;

class FileHelper
{
	public:

	static vector<string> ReadFileToStringVector(string filepath);
	static vector<int> ReadFileToIntVector(string filepath);
	static string ReadFileToString(string filepath);
};