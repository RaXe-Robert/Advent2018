#pragma once

#include <vector>
#include <string>

class FileHelper
{
	public:

	static std::vector<std::string> ReadFileToStringVector(std::string filepath);
	static std::vector<int> ReadFileToIntVector(std::string filepath);
	static std::string ReadFileToString(std::string filepath);
};