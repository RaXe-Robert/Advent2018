#include "Day2.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <string>

using namespace std;

void Day2::Solve()
{
	cout << "Day2 part 1" << endl;
		
	ifstream inFile("D:\\input2.txt");

	if (!inFile) {
		cerr << "Unable to open file input2.txt" << endl;
		exit(1);
	}
	
	int doubleCounter = 0;
	int tripleCounter = 0;

	string line;
	while (inFile >> line) {

		cout << line << endl;

		map<char, int> charOccurrences;

		for (auto& x : line) {
			auto iterator = charOccurrences.find(x);
			if (iterator != charOccurrences.end()) {
				charOccurrences[x] += 1;
			}
			else {
				charOccurrences.insert(make_pair(x, 1));
			}
		}

		bool countedDouble = false;
		bool countedTriple = false;

		map<char, int>::iterator it;
		for (it = charOccurrences.begin(); it != charOccurrences.end(); it++)
		{
			if (it->second == 2 && !countedDouble) {
				doubleCounter++;
				countedDouble = true;
			}

			if (it->second == 3 && !countedTriple) {
				tripleCounter++;
				countedTriple = true;
			}
		}
	}

	cout << "Answer: " << doubleCounter * tripleCounter << endl;

	inFile.close();
}