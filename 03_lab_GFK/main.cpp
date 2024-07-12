#include <wx/wxprec.h>
#include "lab03MyFrame.h"

class MyApp : public wxApp {

public:

	virtual bool OnInit();
	virtual int OnExit() { return 0; }

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	SetProcessDPIAware();
	wxFrame* mainFrame = new lab03MyFrame(NULL);
	mainFrame->Show(true);
	SetTopWindow(mainFrame);

	return true;
}