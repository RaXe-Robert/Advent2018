/*
https://adventofcode.com/2018/day/3
*/

#define DAY3_FILE_SIZE 1323
#define DAY3_BUFFER_SIZE 30

struct claim {
	int id;
	int x_start;
	int x_end;
	int y_start;
	int y_end;
};

void part1(claim claims[])
{
	printf("[Day03][1] Started\n");

	std::regex regex("#(\\d+)...(\\d+),(\\d+):.(\\d+)x(\\d+)");
	std::cmatch match;

	std::map<int, std::map<int, int>> claimsMap;
	for (auto i = 0; i < DAY3_FILE_SIZE; i++) {
		auto claim = claims[i];

		for (auto x = claim.x_start; x < claim.x_end; x++) {
			auto it = claimsMap.find(x);
			if (it == claimsMap.end()) {
				auto pair = std::make_pair(x, std::map<int, int>());
				claimsMap.insert(pair);
			}

			auto& row = claimsMap.at(x);
			for (auto y = claim.y_start; y < claim.y_end; y++) {
				auto rowIt = row.find(y);
				if (rowIt == row.end()) {
					auto pair = std::make_pair(y, 1);
					row.insert(pair);
				}
				else
					(*rowIt).second += 1;
			}
		}
	}
	
	int count = 0;

	for (auto x : claimsMap) {
		for (auto y : x.second) {
			if (y.second >= 2)
				count++;
		}
	}

	printf("[Day03][1] Answer: %i\n\n", count);
}

void part2(claim claims[])
{
	printf("[Day03][2] Started\n");

	std::regex regex("#(\\d+)...(\\d+),(\\d+):.(\\d+)x(\\d+)");
	std::cmatch match;

	std::set<int> noOverlap;
	// int's are respectively: x, y, claimId
	std::map<int, std::map<int, int>> claimsMap;

	for (auto i = 0; i < DAY3_FILE_SIZE; i++) {
		auto claim = claims[i];
		noOverlap.insert(claim.id);

		for (auto x = claim.x_start; x < claim.x_end; x++) {
			if (claimsMap.find(x) == claimsMap.end()) {
				auto pair = std::make_pair(x, std::map<int, int>());
				claimsMap.insert(pair);
			}

			auto& col = claimsMap.at(x);
			for (auto y = claim.y_start; y < claim.y_end; y++) {
				auto row = col.find(y);
				if (row == col.end()) {
					auto claimPair = std::make_pair(y, claim.id);
					col.insert(claimPair);
				}
				else {
					auto existingClaimId = row->second;
					if (existingClaimId == claim.id)
						continue;
					
					if (existingClaimId != -1) {
						noOverlap.erase(existingClaimId);
						row->second = -1;
					}

					noOverlap.erase(claim.id);
				}
			}
		}
	}

	for (auto number : noOverlap) {
		printf("[Day03][2] Answer: %i\n\n", number);
		return;
	}

	printf("[Day03][2] Answer: ERROR\n\n");
}

void day03(const char* filepath)
{
	std::regex regex("#(\\d+)...(\\d+),(\\d+):.(\\d+)x(\\d+)");
	std::cmatch match;

	auto file = fopen(filepath, "rb");

	auto buffer = reinterpret_cast<char*>(malloc(DAY3_BUFFER_SIZE));

	claim claims[DAY3_FILE_SIZE];

	for (auto i = 0; fgets(buffer, DAY3_BUFFER_SIZE, file); i++) {
		if (!std::regex_search(buffer, match, regex))
			continue;

		int claimId = stoi(match[1]);
		int x_start = stoi(match[2]);
		int y_start = stoi(match[3]);
		int x_end = x_start + stoi(match[4]);
		int y_end = y_start + stoi(match[5]);
		
		struct claim claim;
		claim.id = claimId;
		claim.x_start = x_start;
		claim.x_end = x_end;
		claim.y_start = y_start;
		claim.y_end= y_end;
		claims[i] = claim;
	}
	fclose(file);

	part1(claims);
	part2(claims);
}