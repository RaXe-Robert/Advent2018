/*
https://adventofcode.com/2018/day/7
*/

constexpr auto DAY7_FILE_LENGTH = 101;
constexpr auto DAY7_BUFFER_SIZE = 64;

void day07(const char* filepath)
{
	auto buffer = new char[DAY7_FILE_LENGTH * DAY7_BUFFER_SIZE];
	auto start = buffer;
	auto file = fopen(filepath, "rb");
	while (fgets(buffer, DAY7_BUFFER_SIZE, file))
		buffer += DAY7_BUFFER_SIZE;
	fclose(file);

	delete start;
}