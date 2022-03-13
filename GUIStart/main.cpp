#include <CtrlLib/CtrlLib.h>

using namespace Upp;

GUI_APP_MAIN
{
	TopWindow w;
	w.Title("My Application").Zoomable().Sizeable();
	w.SetRect(0,0,200,300);
	w.SetAlpha(100);
	w.Run();
	PromptOK("Application closing!"); //Information dialog
}
