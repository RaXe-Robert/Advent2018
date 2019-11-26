/*
https://adventofcode.com/2018/day/7
*/

constexpr s32 ALPHABET_LENGTH = 26;
constexpr s32 ASCII_OFFSET = 65;

void day07(const char* filepath)
{
	s32* steps;
	steps = reinterpret_cast<s32*>(malloc(sizeof(s32) * ALPHABET_LENGTH * ALPHABET_LENGTH));
	memset(steps, 0, sizeof(s32) * ALPHABET_LENGTH * ALPHABET_LENGTH);

	char* buffer = new char[64];

	auto file = fopen(filepath, "rb");
	while (fgets(buffer, 64, file)) 
	{
		s32 step = buffer[5] - ASCII_OFFSET;
		s32 stepRequired = buffer[36] - ASCII_OFFSET;

		auto ptr = steps + (step * ALPHABET_LENGTH) + stepRequired;	
		*ptr = 1;
	}
	fclose(file);

	for (auto x = 0; x < ALPHABET_LENGTH; x++)
	{
		char step = x + ASCII_OFFSET;
		printf("%c, requires: ", step);
		for (auto y = 0; y < ALPHABET_LENGTH; y++)
		{
			bool required = *(steps + (x * ALPHABET_LENGTH) + y) == 1;
			if (required)
				printf("%c ", y + ASCII_OFFSET);
			else
				printf("- ", 0);

		}
		printf("\n");
	} 	

	delete buffer;
}