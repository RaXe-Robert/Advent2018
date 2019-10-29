#include "FileHelper.h"

#include <windows.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

/*
TODO: Generics?
*/

std::vector<std::string> FileHelper::ReadFileToStringVector(std::string filepath)
{

	std::ifstream inFile(filepath);

	if (!inFile) {
		std::cerr << "Unable to open file @" << filepath << std::endl;
	}

	// Map file to vector for convenience
	std::string line;
	std::vector<std::string> data;
	while (getline(inFile, line)) {
		data.push_back(line);
	}

	inFile.close();

	return data;
}

std::vector<int> FileHelper::ReadFileToIntVector(std::string filepath)
{
	std::ifstream inFile(filepath, true);

	if (!inFile) {
		std::cerr << "Unable to open file @" << filepath << std::endl;
	}

	// Map file to vector for convenience
	std::string line;
	std::vector<int> data;
	while (getline(inFile, line)) {
		data.push_back(stoi(line));
	}

	inFile.close();

	return data;
}

std::string FileHelper::ReadFileToString(std::string filepath)
{
	std::ifstream inFile(filepath, true);

	if (!inFile) {
		std::cerr << "Unable to open file @" << filepath << std::endl;
	}

	std::string line;
	std::string data;
	while (getline(inFile, line)) {
		data += line;
	}

	inFile.close();

	return data;
}