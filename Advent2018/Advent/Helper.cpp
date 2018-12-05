#include "Helper.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
TODO: Generics?
*/

vector<string> Helper::ReadFileToStringVector(string filepath)
{
	ifstream inFile(filepath);

	if (!inFile) {
		cerr << "Unable to open file @" << filepath << endl;
	}

	// Map file to vector for convenience
	string line;
	vector<string> data;
	while (inFile >> line) {
		data.push_back(line);
	}

	inFile.close();

	return data;
}

vector<int> Helper::ReadFileToIntVector(string filepath)
{
	ifstream inFile(filepath);

	if (!inFile) {
		cerr << "Unable to open file @" << filepath << endl;
	}

	// Map file to vector for convenience
	int line;
	vector<int> data;
	while (inFile >> line) {
		data.push_back(line);
	}

	inFile.close();

	return data;
}