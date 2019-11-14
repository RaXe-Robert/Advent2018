/*
https://adventofcode.com/2018/day/2
*/

#define DAY2_FILE_LENGTH 250
#define DAY2_BUFFER_SIZE 28

void part1(char* data)
{
	printf("[Day02][1]\n");

	int doubleCounter = 0;
	int tripleCounter = 0;

	char* ptr = data;

	for (auto i = 0; i < DAY2_FILE_LENGTH; i++) {
		char* line = ptr + DAY2_BUFFER_SIZE * i;

		printf("[Day02][1] %s\n", line);
		std::map<char, int> charOccurrences;

		while (*line++ != '\0') {
			auto iterator = charOccurrences.find(*line);
			if (iterator != charOccurrences.end())
				charOccurrences[*line] += 1;
			else
				charOccurrences.insert(std::make_pair(*line, 1));
		}

		bool countedDouble = false;
		bool countedTriple = false;

		std::map<char, int>::iterator it;
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

	printf("[Day02][1] Answer: %i\n", doubleCounter * tripleCounter);
}

void part2(char* data)
{
	printf("[Day02][2]\n");

	char* ptr = data;

	for (size_t x = 0; x != DAY2_FILE_LENGTH; ++x) {
		// Compare against all other strings, except for itself
		for (size_t y = 0; y != DAY2_FILE_LENGTH; ++y) {
			if (x == y)
				continue;

			int differenceCount = 0;
			std::string result = "";

			// Compare characters
			char* line_l = ptr + DAY2_BUFFER_SIZE * x;
			char* line_r = ptr + DAY2_BUFFER_SIZE * y;

			for (auto i = 0; *line_l++ != '\0'; i++) {
				//std::cout << "[Day02][2] L: " << line_l[i] << " R: " << line_r[i] << std::endl;

				if (line_l[i] != line_r[i])
					differenceCount++;
				else
					result += line_l[i];

				if (differenceCount > 1)
					break;
			}

			if (differenceCount == 1) {
				std::cout << "[Day02][2] Answer: " << result << std::endl;
				return;
			}
		}
	}

	std::cout << "[Day02][2] Failed" << std::endl;
}

void day02(const char* filepath, char* buffer)
{
	auto start = buffer;
	auto file = fopen(filepath, "rb");
	while (fgets(buffer, DAY2_BUFFER_SIZE, file))
		buffer += DAY2_BUFFER_SIZE;
	fclose(file);

	part1(start);
	part2(start);
}
