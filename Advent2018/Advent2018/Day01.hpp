/*
https://adventofcode.com/2018/day/1
*/


void day01(const char* filepath)
{
	printf("[Day01][1] Started\n");

	auto file = fopen(filepath, "rb");

	std::vector<int> data;
	char buffer[100];

	int frequency = 0;

	while (!feof(file))
	{
		char* line = fgets(buffer, 100, file);
		if (line == NULL)
			break;

		int val = atoi(line);
		frequency += val;
		data.push_back(val);
	}

	fclose(file);
	printf("[Day01][1] Answer: %i\n\n", frequency);

	printf("[Day01][2] Started\n");
	std::set<int> set = { };
	frequency = 0;

	while (true) {
		for (int i : data) {
			frequency += i;
			auto x = set.insert(frequency);
			if (!x.second) {
				printf("[Day01][2] Answer: %i\n\n", frequency);
				return;
			}
		}
	}
}