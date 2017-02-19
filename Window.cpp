/*
 * Copyright 2017, Adrien Destugues, pulkomandy@pulkomandy.tk
 * Distributed under terms of the MIT license.
 */

#include <CheckBox.h>
#include <GroupView.h>
#include <ListView.h>
#include <ScrollBar.h>
#include <StringView.h>
#include <TextView.h>
#include <Window.h>

class Window: public BWindow
{
	public:
										Window();

						void			AddTask(BString title);

						void			MessageReceived(BMessage* message);
	private:
						void			ShowTaskDetails(int32 index);
						void			PopulateList(BListView* list, BMessage& msg);
	private:
						BListView*		fTaskList;

						BStringView*	fTaskTitle;
						BCheckBox*		fPublished;
						BStringView*	fDuration;
						BStringView*	fInstanceCount;
						BTextView*		fDescription;

						BListView*		fMentorList;
						BListView*		fTagsList;

		static const	int32			kSelectionChanged = '_SEL';
};

Window::Window()
	: BWindow(BRect(100, 100, 300, 400), "GCI Tool", B_DOCUMENT_WINDOW,
		B_AUTO_UPDATE_SIZE_LIMITS | B_QUIT_ON_WINDOW_CLOSE)
{
	SetLayout(new BGroupLayout(B_VERTICAL));

	fTaskList = new BListView("taskList", B_SINGLE_SELECTION_LIST);
	BMessage* message = new BMessage(kSelectionChanged);
	fTaskList->SetSelectionMessage(message);
	fTaskList->SetExplicitMinSize(BSize(200, B_SIZE_UNSET));

	BGroupView* root = new BGroupView("root", B_HORIZONTAL);

	AddChild(root);
	root->SetViewUIColor(B_PANEL_BACKGROUND_COLOR);
	root->GroupLayout()->SetInsets(B_USE_WINDOW_SPACING);

	BScrollBar* sb = new BScrollBar("scroll", fTaskList, 0, 1, B_VERTICAL);
	root->AddChild(fTaskList);
	root->AddChild(sb);

	BGroupView* g2 = new BGroupView(B_VERTICAL);
	root->AddChild(g2);

	BGroupView* gt = new BGroupView(B_HORIZONTAL);
	fTaskTitle = new BStringView("title", "- TASK NAME -");
	BFont bigFont = be_plain_font;
	bigFont.SetSize(bigFont.Size() * 1.5);
	fTaskTitle->SetFont(&bigFont);
	fTaskTitle->SetExplicitMinSize(BSize(500, B_SIZE_UNSET));

	gt->AddChild(fTaskTitle);
	g2->AddChild(gt);

	BGroupView* g3 = new BGroupView(B_HORIZONTAL);
	g2->AddChild(g3);

	fPublished = new BCheckBox("published");
	fDuration = new BStringView("duration", "N days");
fInstanceCount = new BStringView("instances", "1 instance");

	g3->AddChild(fPublished);
	g3->AddChild(fDuration);
	g3->AddChild(fInstanceCount);

	fDescription = new BTextView("description");
	fDescription->SetExplicitMinSize(BSize(B_SIZE_UNSET, 200));
	g2->AddChild(fDescription);

	BGroupView* g4 = new BGroupView(B_HORIZONTAL);
	g2->AddChild(g4);

	fMentorList = new BListView("mentors");
	fTagsList = new BListView("tags");
	g4->AddChild(fMentorList);
	g4->AddChild(fTagsList);

	fMentorList->SetExplicitMinSize(BSize(150, B_SIZE_UNSET));
	fTagsList->SetExplicitMinSize(BSize(100, B_SIZE_UNSET));

	BGroupView* g5 = new BGroupView(B_VERTICAL);
	BCheckBox* b0 = new BCheckBox("Coding");
	BCheckBox* b1 = new BCheckBox("User interface");
	BCheckBox* b2 = new BCheckBox("Documentation & Training");
	BCheckBox* b3 = new BCheckBox("Quality Assurance");
	BCheckBox* b4 = new BCheckBox("Outreach & Research");
	g5->AddChild(b0);
	g5->AddChild(b1);
	g5->AddChild(b2);
	g5->AddChild(b3);
	g5->AddChild(b4);

	g4->AddChild(g5);
}


void
Window::AddTask(BString name)
{
	fTaskList->AddItem(new BStringItem(name));
}


void
Window::MessageReceived(BMessage* message)
{
	switch(message->what)
	{
		case kSelectionChanged:
		{
			int32 index = message->FindInt32("index");
			ShowTaskDetails(index);
			break;
		}

		default:
			BWindow::MessageReceived(message);
			break;
	}
}


void
Window::ShowTaskDetails(int32 index)
{
	Application* app = (Application*)be_app;
	BMessage* data = app->GetTaskData(index);

	BString title = data->FindString("name");
	fTaskTitle->SetText(title);

	fPublished->SetValue(data->FindInt32("status") - 1);
	BString duration;
	duration.SetToFormat("%d days", (int)data->FindDouble("time_to_complete_in_days"));
	fDuration->SetText(duration);

	BString instances;
	instances.SetToFormat("%d instances", (int)data->FindDouble("max_instances"));
	fInstanceCount->SetText(instances);

	fDescription->SetText(data->FindString("description"));

	BMessage m;
	data->FindMessage("mentors", &m);
	PopulateList(fMentorList, m);

	data->FindMessage("tags", &m);
	PopulateList(fTagsList, m);

	// last_modified, is_beginner, categories
	// program_year, private_metadata, id

	delete data;
}


void
Window::PopulateList(BListView* list, BMessage& msg)
{
	int k;
	BString mentor;
	list->MakeEmpty();
	for(k = 0;;k++)
	{
		BString idx;
		idx << k;

		status_t r = msg.FindString(idx, &mentor);
		if (r != B_OK)
			break;
		list->AddItem(new BStringItem(mentor));
	}
}
