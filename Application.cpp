/*
 * Copyright 2017, Adrien Destugues, pulkomandy@pulkomandy.tk
 * Distributed under terms of the MIT license.
 */


#include "Application.h"

#include "Window.cpp"


Application::Application(const char* filename)
	: BApplication("application/PulkoMandy-GCITool")
{
	BFile file(filename, B_READ_ONLY);
	off_t size;

	if (file.GetSize(&size) != B_OK)
	{
		fprintf(stderr, "%s is not a file\n", filename);
		return;
	}

	char* data = (char*)malloc(size);

	file.Read(data, size);

	BMessage parsed;
	if (BPrivate::BJson::Parse(data, parsed) != B_OK)
	{
		fprintf(stderr, "%s is not a JSON file\n", filename);
		return;
	}

	free(data);

	parsed.FindMessage("results", &fTaskData);

	fTaskCount = (int)parsed.FindDouble("count");
}


void
Application::ReadyToRun()
{
	Window* w = new Window();

	for (int i = 0; i < fTaskCount; i++)
	{
		BMessage task;
		BString tmp;
		tmp << i;
		fTaskData.FindMessage(tmp, 0, &task);

		tmp = task.FindString("name");

		//printf("%s\n", tmp.String());
		w->AddTask(tmp);
	}

	w->Show();
}


BMessage*
Application::GetTaskData(int32 index)
{
	if (index >= fTaskCount)
		return NULL;

	BMessage* task = new BMessage();
	BString tmp;
	tmp << index;
	fTaskData.FindMessage(tmp, 0, task);

	return task;
}
