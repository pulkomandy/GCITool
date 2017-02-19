/*
 * Copyright 2017, Adrien Destugues, pulkomandy@pulkomandy.tk
 * Distributed under terms of the MIT license.
 */


class Application: public BApplication
{
	public:
					Application(const char* file);

		void		ReadyToRun();

		BMessage*	GetTaskData(int32 index);

	private:
		BMessage	fTaskData;
		int			fTaskCount;
};

