/*
https://adventofcode.com/2018/day/7
*/

constexpr s32 ALPHABET_LENGTH = 26;
constexpr s32 ASCII_OFFSET = 65;

inline bool
containsChar(char* arr, s32 size, char c)
{
	for (auto it = arr; *it; ++it)
	{
		if (*it == c)
			return true;
	}
	return false;
}

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

	char* part1 = new char[ALPHABET_LENGTH + 1];
	memset(part1, 0, sizeof(char) * ALPHABET_LENGTH);
	part1[ALPHABET_LENGTH] = '\0';

	int part1_length = 0;

	for (char x = 'A'; x <= 'Z'; x++)
	{
		auto index = x - ASCII_OFFSET;

		if (containsChar(part1, part1_length, x))
			continue;

		printf("%c, requires: ", x);

		bool ready = true;

		for (auto y = 0; y < ALPHABET_LENGTH; y++)
		{
			bool required = steps[(index * ALPHABET_LENGTH) + y] == 1;
			if (required)
			{
				printf("%c ", y + ASCII_OFFSET);
				ready = false;
			}
			else
				printf("- ");
		}

		if (ready)
		{
			part1[part1_length] = x;
			part1_length++;

			for (auto i = 0; i < ALPHABET_LENGTH; i++)
			{
				steps[i * ALPHABET_LENGTH + index] = 0;
			}
			x = 'A' - 1;
			printf("\n");
		}

		printf("\n");
	}

	printf("%s\n", part1);


	delete buffer;
}