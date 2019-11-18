struct Polymer
{
	char* data;
	int32_t size;
};

Polymer solvePolymer(Polymer polymer)
{
	std::locale loc;

	auto dataPtr = polymer.data;
	int32_t* sizePtr = &polymer.size;
	
	while (true) {
		bool stop = true;

		for (auto i = polymer.size - 2; i >= 0; i--) {
			// Check if same character
			if (tolower(dataPtr[i], loc) != tolower(dataPtr[i + 1], loc))
				continue;

			auto l = isupper(dataPtr[i]);
			auto r = isupper(dataPtr[i + 1]);
			if (l != r) {
				memmove(&dataPtr[i], &dataPtr[i + 2], polymer.size - i);
				polymer.size -= 2;
				stop = false;
			}
		}

		if (stop)
			break;
	}

	return polymer;
}

std::string excludeCharacter(std::string polymer, char character)
{
	std::locale loc;

	for (auto i = polymer.size(); i >= 1; i--) {
		printf("e%i\n", i);
		if (tolower(polymer[i], loc) == character)
			polymer.erase(i, 1);
	}

	return polymer;
}

void day05(const char* filepath)
{
	printf("[Day05][1] Started\n");

	auto file = fopen(filepath, "rb");
	int32_t size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	auto buffer = reinterpret_cast<char*>(malloc(size + 1));
	fread(buffer, 1, size, file);
	fclose(file);

	auto polymer = new Polymer{
		buffer,
		size
	};

	std::vector<char> characters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	auto result = solvePolymer(*polymer);

	// TODO: size is 1 too big since we count the \n character
	printf("[Day05][1] Answer: %zu\n\n", result.size);

	/*
	printf("[Day05][2] Started\n");

	size_t smallestResult = result;
	char bestCharacter;
	for (auto& character : characters) {
		std::string modifiedPolymer = excludeCharacter(polymer, character);
		result = solvePolymer(modifiedPolymer);

		if (result <= smallestResult) {
			smallestResult = result;
			bestCharacter = character;
		}
	}

	printf("[Day05][2] Answer: %c, with: %zu\n\n", bestCharacter, smallestResult);
	*/
}