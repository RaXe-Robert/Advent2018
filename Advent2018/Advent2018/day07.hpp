/*
https://adventofcode.com/2018/day/7
*/

constexpr s32 ALPHABET_LENGTH = 26;
constexpr s32 ASCII_OFFSET = 65;

struct Worker
{
	char task = 0;
	s32 duration = 0;
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

void day07_part1(s32* steps)
{
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
			bool required = steps[x * ALPHABET_LENGTH + y] == 1;
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
}

void day07_part2(s32* steps)
{
	char* busy = new char[ALPHABET_LENGTH + 1];
	memset(busy, 0, sizeof(char) * ALPHABET_LENGTH);
	busy[ALPHABET_LENGTH] = '\0';
	s32 busy_length = 0;

	char* done = new char[ALPHABET_LENGTH + 1];
	memset(done, 0, sizeof(char) * ALPHABET_LENGTH);
	done[ALPHABET_LENGTH] = '\0';
	s32 done_length = 0;

	s32 part2 = 0;

	const auto workerCount = 5;
	auto workers = new Worker[workerCount];

	for (; part2 < (1 << 16); part2++)
	{
		for (auto i = 0; i < workerCount; i++)
		{
			auto worker = &workers[i];
			if (worker->task == 0)
				continue;

			worker->duration--;
			if (worker->duration > 0)
				continue;

			for (auto ii = 0; ii < ALPHABET_LENGTH; ii++)
				steps[ii * ALPHABET_LENGTH + (worker->task - ASCII_OFFSET)] = 0;

			done[done_length] = worker->task;
			done_length++;

			worker->duration = 0;
			worker->task = 0;
		}

		for (char x = 0; x < ALPHABET_LENGTH; x++)
		{
			char c = x + ASCII_OFFSET;
			if (containsChar(busy, busy_length, c))
				continue;

			bool available = true;
			for (auto y = 0; y < ALPHABET_LENGTH; y++)
			{
				bool required = steps[x * ALPHABET_LENGTH + y] == 1;
				if (required)
					available = false;
			}
			if (!available)
				continue;

			for (auto i = 0; i < workerCount; i++)
			{
				auto worker = &workers[i];
				if (worker->task == 0)
				{
					worker->task = c;
					worker->duration = 60 + (x + 1);

					busy[busy_length] = c;
					busy_length++;
					break;
				}
			}
		}

		if (done_length >= ALPHABET_LENGTH)
			break;
	}

	printf("[Day07][2] Answer: %i\n", part2);
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
		s32 stepRequired = buffer[5] - ASCII_OFFSET;
		s32 step = buffer[36] - ASCII_OFFSET;

		auto ptr = &steps[step * ALPHABET_LENGTH + stepRequired];	
		*ptr = 1;
	}

	fclose(file);
	delete[] buffer;

	s32* steps2;
	steps2 = reinterpret_cast<s32*>(malloc(sizeof(s32) * ALPHABET_LENGTH * ALPHABET_LENGTH));
	memcpy(steps2, steps, sizeof(s32) * ALPHABET_LENGTH * ALPHABET_LENGTH);

	day07_part1(steps);
	day07_part2(steps2);

	free(steps);
	free(steps2);
}