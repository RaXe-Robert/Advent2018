/*
https://adventofcode.com/2018/day/8

2 3 0 3 10 11 12 1 1 0 1 99 2 1 1 2
A----------------------------------
	B----------- C-----------
					 D-----

*/


struct Node
{
	Node* children = 0;
	s32 childCount;

	s32* metadata = 0;
	s32 metadataCount;

	// Inclusive
	s32 start;
	// Inclusive
	s32 end;
};

Node
createNode(s32* arr, s32 start, s32& part1)
{
	Node node;
	node.start = start;

	node.childCount = arr[start];
	if (node.childCount > 0)
		node.children = new Node[node.childCount];

	node.metadataCount = arr[start + 1];
	if (node.metadataCount > 0)
		node.metadata = new s32[node.metadataCount];

	node.end = (node.start + 1) + node.metadataCount;

	if (node.childCount > 0)
	{
		auto childStart = node.start + 2;
		for (auto i = 0; i < node.childCount; i++)
		{
			auto child = createNode(arr, childStart, part1);
			node.children[i] = child;
			
			// + 1 since end is inclusive
			s32 childSize = (child.end - child.start) + 1;
			node.end += childSize;

			childStart += childSize;
		}
	}

	if (node.metadataCount > 0)
	{
		auto start = node.end + 1 - node.metadataCount;
		for (auto i = 0; i < node.metadataCount; i++)
		{
			node.metadata[i] = arr[start + i];
			part1 += node.metadata[i];
		}
	}

	return node;
}

void day08(const char* filepath)
{
	char* buffer = new char[3]{ 0, 0, '\0' };
	s32 buffer_length = 0;

	auto file = fopen(filepath, "rb");

	s32 size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	s32* arr;
	arr = reinterpret_cast<s32*>(malloc(sizeof(s32) * size));
	auto arr_length = 0;

	while (1)
	{
		s32 c = fgetc(file);
		if (c == 32 || c == EOF)
		{
			s16 num = atoi(buffer);
			arr[arr_length] = num;
			arr_length++;

			memset(buffer, 0, buffer_length);
			buffer_length = 0;

			if (c == EOF)
				break;
		}
		else
		{
			char num_part = (char)c;
			buffer[buffer_length] = num_part;
			buffer_length++;
		}
	}

	s32 part1 = 0;
	Node rootNode = createNode(arr, 0, part1);

	printf("[Day08][1] Answer: %i\n", part1);

	fclose(file);

	delete[] buffer;
	free(arr);

}