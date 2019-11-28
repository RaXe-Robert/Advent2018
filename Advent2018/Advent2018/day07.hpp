/*
https://adventofcode.com/2018/day/7
*/

constexpr s32 ALPHABET_LENGTH = 26;
constexpr s32 ASCII_OFFSET = 65;

struct Worker
{
	char task;
	s32 duration;
};

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


	s32* steps2;
	steps2 = reinterpret_cast<s32*>(malloc(sizeof(s32) * ALPHABET_LENGTH * ALPHABET_LENGTH));
	memset(steps2, 0, sizeof(s32) * ALPHABET_LENGTH * ALPHABET_LENGTH);

	char* buffer = new char[64];

	auto file = fopen(filepath, "rb");
	while (fgets(buffer, 64, file)) 
	{
		s32 stepRequired = buffer[5] - ASCII_OFFSET;
		s32 step = buffer[36] - ASCII_OFFSET;

		auto ptr = &steps[step * ALPHABET_LENGTH + stepRequired];	
		*ptr = 1;

		auto ptr2 = &steps2[step * ALPHABET_LENGTH + stepRequired];
		*ptr2 = 1;
	}
	fclose(file);


	char* part1 = new char[ALPHABET_LENGTH + 1];
	memset(part1, 0, sizeof(char) * ALPHABET_LENGTH);
	part1[ALPHABET_LENGTH] = '\0';

	s32 part1_length = 0;

	for (char x = 0; x < ALPHABET_LENGTH; x++)
	{
		char c = x + ASCII_OFFSET;
		if (containsChar(part1, part1_length, c))
			continue;

		bool available = true;

		for (auto y = 0; y < ALPHABET_LENGTH; y++)
		{
			bool required = steps[(x * ALPHABET_LENGTH) + y] == 1;
			if (required)
			{
				available = false;
				break;
			}
		}

		if (available)
		{
			part1[part1_length] = c;
			part1_length++;

			for (auto i = 0; i < ALPHABET_LENGTH; i++)
				steps[i * ALPHABET_LENGTH + x] = 0;

			x = -1;
		}
	}

	printf("[Day07][1] Answer: %s\n", part1);

	char* busy = new char[ALPHABET_LENGTH + 1];
	memset(busy, 0, sizeof(char) * ALPHABET_LENGTH);
	busy[ALPHABET_LENGTH] = '\0';

	s32 busy_length = 0;

	s32 part2 = 0;

	const auto workerCount = 4;
	auto workers = new Worker[workerCount];

	while(1)
	{
		for (char x = 0; x < ALPHABET_LENGTH; x++)
		{
			char c = x + ASCII_OFFSET;
			if (containsChar(busy, ALPHABET_LENGTH, c))
				continue;

			bool available = true;

			for (auto y = 0; y < ALPHABET_LENGTH; y++)
			{
				bool required = steps2[(x * ALPHABET_LENGTH) + y] == 1;
				if (required)
				{
					available = false;
					break;
				}
			}

			if (available)
			{
				auto stepTime = 60 + x;

				for (auto i = 0; i < workerCount; i++)
				{
					if (workers[i].task == 0)
					{
						workers[i].task = c;
						workers[i].duration = stepTime;
						
						busy[busy_length] = c;
						busy_length++;
						break;
					}
				}

				for (auto i = 0; i < ALPHABET_LENGTH; i++)
					steps2[i * ALPHABET_LENGTH + x] = 0;
			}
		}

		s32 shortestStep = -1;
		for (auto i = 0; i < workerCount; i++)
		{
			// Idle
			if (workers[i].duration == 0)
				continue;

			if (shortestStep == -1 || workers[i].duration < shortestStep)
				shortestStep = workers[i].duration;
		}

		if (shortestStep > 0)
			part2 += shortestStep;

		for (auto i = 0; i < workerCount; i++)
		{
			workers[i].duration -= shortestStep;
			if (workers[i].duration <= 0)
			{
				for (auto ii = 0; ii < ALPHABET_LENGTH; ii++)
					steps2[ii * ALPHABET_LENGTH + (workers[i].task - ASCII_OFFSET)] = 0;

				workers[i].task = 0;
			}
		}


		// Safe guard
		if (part2 >= 1 << 31)
			break;
	}

	printf("[Day07][2] Answer: %s\n", part2);

	free(buffer);
}