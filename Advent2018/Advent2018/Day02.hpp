/*
https://adventofcode.com/2018/day/2
*/

// TODO: optional, remove this so that any file would work
constexpr s32 DAY2_FILE_LENGTH = 250;
// 26 characters + \r\n;
constexpr s32 DAY2_BUFFER_SIZE = 30;

void day02_part1(char* data)
{
	s32 doubeCounter = 0;
	s32 tripleCounter = 0;

	char* dataPtr = data;

	for (auto i = 0; i < DAY2_FILE_LENGTH; i++) 
	{
		char* line = dataPtr + DAY2_BUFFER_SIZE * i;

		std::map<char, int> chars;
		auto doubleCount = 0;
		auto tripleCount = 0;

		for (auto j = 0; j < DAY2_BUFFER_SIZE; j++) 
		{
			auto c = line[j];

			if (chars.find(c) != chars.end()) 
			{
				auto charCount = ++chars[c];

				if (charCount == 2)
					doubleCount++;
				else if (charCount == 3) 
				{
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

	printf("[Day02][1] Answer: %i\n", doubeCounter * tripleCounter);
}

void day02_part2(char* data)
{
	char* dataPtr = data;

	for (auto x = 0; x < DAY2_FILE_LENGTH; ++x)
	for (auto y = 0; y < DAY2_FILE_LENGTH; ++y) 
	{
		if (x == y)
			continue;

		char* line_x = dataPtr + DAY2_BUFFER_SIZE * x;
		char* line_y = dataPtr + DAY2_BUFFER_SIZE * y;

		char* result = new char[DAY2_BUFFER_SIZE];
		int differenceCount = 0;

		for (auto i = 0; i < DAY2_BUFFER_SIZE; i++)
		{
			auto char_x = line_x + i;
			auto char_y = line_y + i;

			if (*char_x == *char_y)
				*result++ = *char_x;
			else
				differenceCount++;

			if (differenceCount >= 2)
				break;
		}

		if (differenceCount == 1) 
		{
			printf("[_____][2] Answer: %s", result - DAY2_BUFFER_SIZE + differenceCount);
			return;
		}
	}

	printf("[_____][2] Answer: ERROR\n");
}

void day02(const char* filepath)
{
	auto buffer = new char[DAY2_FILE_LENGTH * DAY2_BUFFER_SIZE];
	auto start = buffer;
	auto file = fopen(filepath, "rb");
	while (fgets(buffer, DAY2_BUFFER_SIZE, file))
		buffer += DAY2_BUFFER_SIZE;
	fclose(file);

	day02_part1(start);
	day02_part2(start);

	free(start);
}
