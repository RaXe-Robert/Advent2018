std::vector<char*> ReadFileToStringVector(const char* filepath)
{
	auto file = fopen(filepath, "rb");
	assert(file);

	std::vector<char*> data;
	char* buffer = new char[4096];

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