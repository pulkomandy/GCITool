/*
 * Copyright 2017, Adrien Destugues, pulkomandy@pulkomandy.tk
 * Distributed under terms of the MIT license.
 */


#include <Application.h>
#include <File.h>
#include <private/shared/Json.h>

#include <stdio.h>
#include <stdlib.h>

#include "Application.cpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "%s tasks.json\n", argv[0]);
		return 1;
	}

	Application app(argv[1]);

	app.Run();

	return 0;
}
