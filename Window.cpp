/*
 * Copyright 2017, Adrien Destugues, pulkomandy@pulkomandy.tk
 * Distributed under terms of the MIT license.
 */

#include <ListView.h>
#include <Window.h>

class Window: public BWindow
{
	public:
		Window();
	private:
};

Window::Window
	: BWindow(BRect(100, 100, 300, 400))
{
	BListView* list = new BListView();

	SetLayout(new BGroupLayout(B_VERTICAL));
	AddChild(list);

	list->AddItem(new BStringItem("test1"));
	list->AddItem(new BStringItem("test2"));
}
