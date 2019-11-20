/*
https://adventofcode.com/2018/day/3
*/

#define DAY3_FILE_SIZE 1323
#define DAY3_BUFFER_SIZE 30;

void part1(char* data)
{
	printf("[Day03][1] Started\n");

	std::regex regex("#(\\d+)...(\\d+),(\\d+):.(\\d+)x(\\d+)");
	std::cmatch match;

	std::map<int, std::map<int, int>> claims;
	for (auto i = 0; i < DAY3_FILE_SIZE; i++) {
		auto line = data + i * DAY3_BUFFER_SIZE;
		
		if (!std::regex_search(line, match, regex))
			continue;

		int x_start = stoi(match[2]);
		int y_start = stoi(match[3]);
		int x_end = x_start + stoi(match[4]);
		int y_end = y_start + stoi(match[5]);

		for (auto x = x_start; x < x_end; x++) {
			auto it = claims.find(x);

			if (it == claims.end())
				claims.insert(std::make_pair(x, std::map<int, int>()));

			auto& row = claims.at(x);
			for (auto y = y_start; y < y_end; y++) {
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

	for (auto x : claims) {
		for (auto y : x.second) {
			if (y.second >= 2)
				count++;
		}
	}

	printf("[Day03][1] Answer: %i\n\n", count);
}

void part2(char* data)
{
	printf("[Day03][2] Started\n");

	std::regex regex("#(\\d+)...(\\d+),(\\d+):.(\\d+)x(\\d+)");
	std::cmatch match;

	// Todo we could just remove overlapping claims so only claims that don't overlap remain
	// == we wouldn't have to loop at the end and we can make this a set
	std::map<int, bool> claimsOverlap;
	// int's are respectively: x, y, claimId
	std::map<int, std::map<int, int>> claims;

	for (auto i = 0; i < DAY3_FILE_SIZE; i++) {
		auto line = data + i * DAY3_BUFFER_SIZE;

		if (!std::regex_search(line, match, regex))
			continue;

		int claimId = stoi(match[1]);
		int x_start = stoi(match[2]);
		int y_start = stoi(match[3]);
		int x_end = x_start + stoi(match[4]);
		int y_end = y_start + stoi(match[5]);

		for (auto x = x_start; x < x_end; x++) {
			if (claims.find(x) == claims.end()) {
				auto pair = std::make_pair(x, std::map<int, int>());
				claims.insert(pair);
			}

			auto& col = claims.at(x);
			for (auto y = y_start; y < y_end; y++) {
				if (col.find(y) == col.end()) {
					auto claimPair = std::make_pair(y, claimId);
					col.insert(claimPair);

					auto claimOverlapPair = std::make_pair(claimId, false);
					claimsOverlap.insert(claimOverlapPair);
				}
				else {
					auto existingClaimId = col.at(y);
					if (claimId == existingClaimId)
						continue;

					// Mark existing claim as overlapping
					claimsOverlap.find(existingClaimId)->second = true;
					
					// Mark current claim as overlapping
					auto val = claimsOverlap.find(claimId);
					if (val != claimsOverlap.end())
						val->second = true;
					else {
						auto claimOverlapPair = std::make_pair(claimId, true);
						claimsOverlap.insert(claimOverlapPair);
					}
				}
			}
		}
	}

	for (auto number : claimsOverlap) {
		if (!number.second) {
			printf("[Day03][2] Answer: %i\n\n", number.first);
			return;
		}
	}

	printf("[Day03][2] Answer: ERROR\n\n");
}

void day03(const char* filepath)
{
	auto file = fopen(filepath, "rb");

	auto buffer = reinterpret_cast<char*>(malloc(1323 * 30));
	auto start = buffer;

	while (fgets(buffer, DAY2_BUFFER_SIZE, file))
		buffer += 30;
	fclose(file);

	part1(start);
	part2(start);
}