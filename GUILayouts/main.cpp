#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <GUILayouts/dlg.lay>
#include <CtrlCore/lay.h>

struct MyAppWindow : public WithDlgLayout<TopWindow> {
	MyAppWindow() {
		CtrlLayout(*this, "My Dialog");
		ok.Ok() << Acceptor(IDOK); //set return values for object destructor
		cancel.Cancel() << Rejector(IDCANCEL);
	}
};

GUI_APP_MAIN
{
	MyAppWindow app;
	app.text.SetData("Some text"); // Setdata can be replaced by operator <<=
	app.date1 <<= app.date2 <<= app.date3 <<= GetSysDate();
	app.date1.ClearModify(); //Set flag to unmodified property
	app.date2.Disable(); //Disable editing
	app.date3.SetReadOnly(); //Set as read-only
	switch (app.Run()) {
		case IDOK:
			PromptOK("OK was pressed");
			break;
		case IDCANCEL:
			Exclamation("Cancelled");
	}
	if (app.date1.IsModified()) PromptOK("Date was modified!");
	PromptOK((String) app.text.GetData()); // Getdata can be replaced by operator ~
}
