/*
https://adventofcode.com/2018/day/7
*/

void day07(const char* filepath)
{
	char* buffer = new char[64];

	auto file = fopen(filepath, "rb");
	while (fgets(buffer, 64, file)) {
		char step = buffer[5];
		char stepRequired = buffer[36];
		printf("%c - %c\n", step, stepRequired);
	}
	fclose(file);

	// Read: https://stackoverflow.com/questions/26695393/c-and-when-to-use-delete

	delete buffer;
}