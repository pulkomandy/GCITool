/*
 * Copyright 2017, Adrien Destugues, pulkomandy@pulkomandy.tk
 * Distributed under terms of the MIT license.
 */


#include <File.h>
#include <private/shared/Json.h>

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "%s tasks.json\n", argv[0]);
		return 1;
	}

	BFile file(argv[1], B_READ_ONLY);
	off_t size;

	if (file.GetSize(&size) != B_OK)
	{
		fprintf(stderr, "%s is not a file\n", argv[1]);
		return 2;
	}

	char* data = (char*)malloc(size);

	file.Read(data, size);

	BMessage parsed;
	if (BPrivate::BJson::Parse(parsed, data) != B_OK)
	{
		fprintf(stderr, "%s is not a JSON file\n", argv[1]);
		return 2;
	}

	free(data);

	BMessage results;
	parsed.FindMessage("results", &results);

	int count;
	count = parsed.FindDouble("count");
	for (int i = 0; i < count; i++)
	{
		BMessage task;
		BString tmp;
		tmp << i;
		results.FindMessage(tmp, 0, &task);

		tmp = task.FindString("name");

		printf("%s\n", tmp.String());
	}

	return 0;
}
