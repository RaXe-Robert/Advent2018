/*
https://adventofcode.com/2018/day/1
*/

void day01(const char* filepath)
{
	auto file = fopen(filepath, "rb");

	std::vector<int> data;
	char buffer[32];

	int frequency = 0;

	while (!feof(file))
	{
		char* line = fgets(buffer, 32, file);
		if (line == NULL)
			break;

		int val = atoi(line);
		frequency += val;
		data.push_back(val);
	}

	fclose(file);
	printf("[Day01][1] Answer: %i\n", frequency);

	std::set<int> set = { };
	frequency = 0;

	while (true) 
	for (int i : data) 
	{
		frequency += i;
		auto x = set.insert(frequency);
		if (!x.second) 
		{
			printf("[Day01][2] Answer: %i\n", frequency);
			return;
		}
	}
}