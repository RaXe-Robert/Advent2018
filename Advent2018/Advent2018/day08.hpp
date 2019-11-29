/*
https://adventofcode.com/2018/day/8
*/

struct Node
{
	Node* children;
	s32 childCount;

	s32* metadata;
	s32 metadataCount;

	// Inclusive
	s32 start;
	// Exclusive
	s32 end;
	
};

Node
createNode(s32* arr[], s32 start, s32 end)
{
	auto node = new Node;
	node->start = start;
	node->end = end;

	node->childCount = *arr[start];
	node->children = reinterpret_cast<Node*>(malloc(sizeof(Node) * node->childCount));

	node->metadataCount = *(*arr + start + 1);
	node->metadata = reinterpret_cast<s32*>(malloc(sizeof(s32) * node->metadataCount));
	memcpy(node->metadata, (*arr + (end - 1 - node->metadataCount)), node->metadataCount);

	//for (auto i = node->start + 2; i < end; i++)
	//{
	//	Node* child = createNode(arr, start, end);
	//}

	return *node;
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
			s32 num = atoi(buffer);
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

	Node rootNode = createNode(&arr, 0, arr_length);

	fclose(file);

	delete[] buffer;
	free(arr);

}