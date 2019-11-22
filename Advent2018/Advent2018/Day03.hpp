/*
https://adventofcode.com/2018/day/3
*/

#define DAY3_FILE_SIZE 1323
#define DAY3_BUFFER_SIZE 30

constexpr s32 GRID_SIZE = 1000;

struct claim
{
	s32 id;
	s32 x_start;
	s32 x_end;
	s32 y_start;
	s32 y_end;
};

void part1(claim claims[])
{
	std::regex regex("#(\\d+)...(\\d+),(\\d+):.(\\d+)x(\\d+)");
	std::cmatch match;

	s32* claimGrid = new s32[GRID_SIZE * GRID_SIZE];
	memset(claimGrid, 0, sizeof(s32) * GRID_SIZE * GRID_SIZE);

	int count = 0;
	for (auto i = 0; i < DAY3_FILE_SIZE; i++)
	{
		auto claim = claims[i];
		for (auto x = claim.x_start; x < claim.x_end; x++)
		for (auto y = claim.y_start; y < claim.y_end; y++)
		{
			auto& tile = claimGrid[x * GRID_SIZE + y];
			tile += 1;
			if (tile == 2)
				count++;	
		}
	}

	delete[] claimGrid;
	printf("[Day03][1] Answer: %i\n", count);
}

void part2(claim claims[])
{
	std::regex regex("#(\\d+)...(\\d+),(\\d+):.(\\d+)x(\\d+)");
	std::cmatch match;

	std::set<int> noOverlap;

	s32* claimGrid = new s32[GRID_SIZE * GRID_SIZE];
	memset(claimGrid, -1, sizeof(s32) * GRID_SIZE * GRID_SIZE);

	for (auto i = 0; i < DAY3_FILE_SIZE; i++) 
	{
		auto claim = claims[i];
		noOverlap.insert(claim.id);

		for (auto x = claim.x_start; x < claim.x_end; x++)
		for (auto y = claim.y_start; y < claim.y_end; y++)
		{
			auto existingClaimId = claimGrid[x * GRID_SIZE + y];

			if (existingClaimId == -1)
				claimGrid[x * GRID_SIZE + y] = claim.id;
			else 
			{
				noOverlap.erase(existingClaimId);
				noOverlap.erase(claim.id);
			}
		}
	}

	printf("[Day03][2] Answer: %i\n", *noOverlap.begin());
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