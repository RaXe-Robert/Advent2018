/*
https://adventofcode.com/2018/day/3
*/

#define DAY3_FILE_SIZE 1323
#define DAY3_BUFFER_SIZE 30

struct claim {
	s16 id;
	s16 x_start;
	s16 x_end;
	s16 y_start;
	s16 y_end;
};

void part1(claim claims[])
{
	printf("[Day03][1] Started\n");

	std::regex regex("#(\\d+)...(\\d+),(\\d+):.(\\d+)x(\\d+)");
	std::cmatch match;

	s16* claimGrid = new s16[1000 * 1000];
	memset(claimGrid, 0, sizeof(s16) * 1000 * 1000);

	int count = 0;

	for (auto i = 0; i < DAY3_FILE_SIZE; i++) {
		auto claim = claims[i];

		for (auto x = claim.x_start; x < claim.x_end; x++) {
			for (auto y = claim.y_start; y < claim.y_end; y++) {
				auto tile = claimGrid + (x * 1000 + y);
				*tile += 1;
				if (*tile == 2)
					count++;		
			}
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

	s16* claimGrid = new s16[1000 * 1000];
	memset(claimGrid, -1, sizeof(s16) * 1000 * 1000);

	for (auto i = 0; i < DAY3_FILE_SIZE; i++) {
		auto claim = claims[i];
		noOverlap.insert(claim.id);

		for (auto x = claim.x_start; x < claim.x_end; x++) {
			for (auto y = claim.y_start; y < claim.y_end; y++) {
				auto existingClaimId = claimGrid[x * 1000 + y];

				if (existingClaimId == -1)
					claimGrid[x * 1000 + y] = claim.id;
				else {
					noOverlap.erase(existingClaimId);
					noOverlap.erase(claim.id);
				}
			}
		}
	}

	printf("[Day03][2] Answer: %i\n\n", *noOverlap.begin());
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