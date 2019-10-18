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

vector<string> FileHelper::ReadFileToStringVector(string filepath)
{

	ifstream inFile(filepath);

	if (!inFile) {
		cerr << "Unable to open file @" << filepath << endl;
	}

	// Map file to vector for convenience
	string line;
	vector<string> data;
	while (getline(inFile, line)) {
		data.push_back(line);
	}

	inFile.close();

	return data;
}

vector<int> FileHelper::ReadFileToIntVector(string filepath)
{
	ifstream inFile(filepath, true);

	if (!inFile) {
		cerr << "Unable to open file @" << filepath << endl;
	}

	// Map file to vector for convenience
	string line;
	vector<int> data;
	while (getline(inFile, line)) {
		data.push_back(stoi(line));
	}

	inFile.close();

	return data;
}

string FileHelper::ReadFileToString(string filepath)
{
	ifstream inFile(filepath, true);

	if (!inFile) {
		cerr << "Unable to open file @" << filepath << endl;
	}

	string line;
	string data;
	while (getline(inFile, line)) {
		data += line;
	}

	inFile.close();

	return data;
}