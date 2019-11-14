/*
https://adventofcode.com/2018/day/2
*/

#define DAY2_FILE_LENGTH 250
#define DAY2_BUFFER_SIZE 30 // 26 characters + \r\n

void part1(char* data)
{
	printf("[Day02][1] Started\n");

	int doubeCounter = 0;
	int tripleCounter = 0;

	char* dataPtr = data;

	for (auto i = 0; i < DAY2_FILE_LENGTH; i++) {
		char* line = dataPtr + DAY2_BUFFER_SIZE * i;

		std::map<char, int> chars;
		auto doubleCount = 0;
		auto tripleCount = 0;

		for (auto j = 0; j < DAY2_BUFFER_SIZE; j++) {
			auto c = line[j];

			if (chars.find(c) != chars.end()) {
				auto charCount = ++chars[c];

				if (charCount == 2)
					doubleCount++;
				else if (charCount == 3) {
					tripleCount++;
					doubleCount--;
				}
				else if (charCount > 3)
					tripleCount--;
			}
			else
				chars.insert(std::make_pair(c, 1));
		}

		if (doubleCount > 0)
			doubeCounter++;
		if (tripleCount)
			tripleCounter++;
	}

	printf("[Day02][1] Answer: %i\n\n", doubeCounter * tripleCounter);
}

void part2(char* data)
{
	printf("[Day02][2] Started\n");

	char* dataPtr = data;

	for (auto x = 0; x < DAY2_FILE_LENGTH; ++x) {
		// Compare against all other strings, except for itself
		for (auto y = 0; y < DAY2_FILE_LENGTH; ++y) {
			if (x == y)
				continue;

			char* result = new char[DAY2_BUFFER_SIZE];

			char* line_x = dataPtr + DAY2_BUFFER_SIZE * x;
			char* line_y = dataPtr + DAY2_BUFFER_SIZE * y;

			int differenceCount = 0;
			for (auto i = 0; i < DAY2_BUFFER_SIZE && differenceCount < 2; i++) {
				if (*(line_x + i) == *(line_y + i))
					*result++ = *(line_x + i);
				else
					differenceCount++;
			}

			if (differenceCount == 1) {
				printf("[Day02][2] Answer: %s\n\n", result - DAY2_BUFFER_SIZE + differenceCount);
				return;
			}
		}

	}

	printf("[Day02][2] Answer: ERROR\n\n");
}

void day02(const char* filepath)
{
	auto buffer = new char[DAY2_FILE_LENGTH * DAY2_BUFFER_SIZE];
	auto start = buffer;
	auto file = fopen(filepath, "rb");
	while (fgets(buffer, DAY2_BUFFER_SIZE, file))
		buffer += DAY2_BUFFER_SIZE;
	fclose(file);

	part1(start);
	part2(start);
}
