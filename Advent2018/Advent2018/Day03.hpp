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

	auto dataPtr = data;

	std::map<int, std::map<int, int>> fabricClaims;
	for (auto i = 0; i < DAY3_FILE_SIZE; i++) {
		auto line = dataPtr + i * DAY3_BUFFER_SIZE;
		
		if (std::regex_search(line, match, regex))
		{
			int dataX = stoi(match[2]);
			int dataY = stoi(match[3]);
			int maxX = dataX + stoi(match[4]);
			int maxY = dataY + stoi(match[5]);

			for (int x = dataX; x < maxX; x++) {
				auto it = fabricClaims.find(x);

				if (it == fabricClaims.end())
					fabricClaims.insert(std::make_pair(x, std::map<int, int>()));

				std::map<int, int>& row = fabricClaims.at(x);
				for (int y = dataY; y < maxY; y++) {

					auto rowIt = row.find(y);
					if (rowIt == row.end())
						row.insert(std::make_pair(y, 1));
					else
						rowIt->second += 1;
				}
			}
		}
	}
	
	int count = 0;

	for (auto const& x : fabricClaims) {
		for (auto const& y : x.second) {
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

	std::map<int, bool> numberHasOverlap;

	std::map<int, std::map<int, std::vector<int>>> fabricClaims;
	for (auto i = 0; i < ) {
		auto line = data[i];
		if (std::regex_match(line, match, regex)) {
			int number = stoi(match[1]);
			int dataX = stoi(match[2]);
			int dataY = stoi(match[3]);
			int maxX = dataX + stoi(match[4]);
			int maxY = dataY + stoi(match[5]);

			for (int x = dataX; x < maxX; x++) {
				if (fabricClaims.find(x) == fabricClaims.end())
					fabricClaims.insert(std::make_pair(x, std::map<int, std::vector<int>>()));

				std::map<int, std::vector<int>>& row = fabricClaims.at(x);
				for (int y = dataY; y < maxY; y++) {
					if (row.find(y) == row.end())
						row.insert(std::make_pair(y, std::vector<int>()));
	
					if (numberHasOverlap.find(number) == numberHasOverlap.end())
						numberHasOverlap.insert(std::make_pair(number, false));

					std::vector<int>& column = row.at(y);
					column.push_back(number);

					if (column.size() > 1) {
						for (auto& value : column) {
							numberHasOverlap.find(value)->second = true;
						}
					}
				}
			}
		}
	}

	for (auto& number : numberHasOverlap) {
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
	int32_t size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	auto buffer = reinterpret_cast<char*>(malloc(1323 * 30));
	auto start = buffer;

	while (fgets(buffer, DAY2_BUFFER_SIZE, file))
		buffer += 30;
	fclose(file);
	
	//auto data = buffer;

	//std::vector<char*> data = ReadFileToStringVector(filepath);

	part1(start);
	part2(start);
}