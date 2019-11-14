std::vector<char*> ReadFileToStringVector(const char* filepath)
{
	auto file = fopen(filepath, "rb");
	assert(file);

	std::vector<char*> data;
	char buffer[100];

	while (!feof(file))
	{
		char* line = fgets(buffer, 100, file);
		if (!line)
			break;

		auto x = reinterpret_cast<char*>(malloc(100));
		memcpy(x, line, 100);
		data.push_back(x);
	}

	fclose(file);

	return data;
}

std::vector<int> ReadFileToIntVector(const char* filepath)
{
	auto file = fopen(filepath, "rb");
	assert(file);

	std::vector<int> data;
	char buffer[100];

	while (!feof(file))
	{
		char* line = fgets(buffer, 100, file);
		if (line == NULL)
			break;

		int val = atoi(line);
		data.push_back(val);
	}

	fclose(file);

	return data;
}
