inline
bool is_upper(char c)
{
	return c >= 'A' && c <= 'Z';
}

inline
char to_lowercase(char c)
{
	if (is_upper(c))
		return c + 32;

	return c;
}

struct Polymer
{
	char* data;
	int32_t size;
};

Polymer* copyPolymer(const Polymer polymer)
{
	auto buffer = reinterpret_cast<char*>(malloc(polymer.size + 1));
	memcpy(buffer, polymer.data, polymer.size);

	auto result = new Polymer;
	result->data = buffer;
	result->size = polymer.size;

	return result;
}

Polymer* solvePolymer(const Polymer polymer)
{
	auto copy = copyPolymer(polymer);
	auto dataPtr = copy->data;
	
	bool stop = false;
	while (!stop) 
	{
		stop = true;

		for (auto i = copy->size - 2; i >= 0; i--) 
		{
			// Check if same character
			if (to_lowercase(dataPtr[i]) != to_lowercase(dataPtr[i + 1]))
				continue;

			auto l = is_upper(dataPtr[i]);
			auto r = is_upper(dataPtr[i + 1]);
			if (l != r) 
			{
				memmove(&dataPtr[i], &dataPtr[i + 2], copy->size - i);
				copy->size -= 2;
				stop = false;
			}
		}
	}

	return copy;
}

Polymer* excludeCharacter(const Polymer polymer, char character)
{
	auto copy = copyPolymer(polymer);
	auto dataPtr = copy->data;

	for (auto i = copy->size; i >= 0; i--) 
	{
		if (to_lowercase(dataPtr[i]) != character)
			continue;
		
		memmove(&dataPtr[i], &dataPtr[i + 1], copy->size - i);
		copy->size -= 1;
	}

	return copy;
}

void day05(const char* filepath)
{
	std::vector<char> characters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	auto file = fopen(filepath, "rb");
	int32_t size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	auto buffer = reinterpret_cast<char*>(malloc(size + 1));
	fread(buffer, 1, size, file);
	fclose(file);

	const auto polymer = new Polymer{ buffer, size };
	auto result = solvePolymer(*polymer);
 
	printf("[Day05][1] Answer: %zu (todo: size is 1 too big since we count the \\n character)\n", result->size);
	
	s32 smallestResult = -1;
	char bestCharacter = -1;
	for (auto& character : characters) 
	{
		auto modifiedPolymer = excludeCharacter(*polymer, character);
		result = solvePolymer(*modifiedPolymer);

		if (smallestResult == -1 || result->size <= smallestResult) 
		{
			smallestResult = result->size;
			bestCharacter = character;
		}
	}

	delete result;

	printf("[_____][2] Answer: %zu, character: %c\n\n", smallestResult, bestCharacter);
}