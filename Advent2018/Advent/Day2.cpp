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
	
	map<char, int> charOccurrences;

	string line;
	while (inFile >> line) {

		cout << line << endl;

		for (auto& x : line) {
			auto iterator = charOccurrences.find(x);
			if (iterator != charOccurrences.end()) {
				charOccurrences[x] += 1;
			}
			else {
				charOccurrences.insert(make_pair(x, 1));
			}
			cout << charOccurrences[x];
		}
	}

	inFile.close();
}