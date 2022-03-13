#include <CtrlLib/CtrlLib.h>

using namespace Upp;

GUI_APP_MAIN
{
	PrinterJob pd("My printer job");
	if (pd.Execute()) {
		Draw& w = pd.GetDraw();
		w.StartPage();
		w.DrawText(200,1200, "Hello World!", Arial(600)); // coordinates are dots = 1/600 of an inch
		w.EndPage();
		w.StartPage();
		w.DrawText(200,1200,"Second page", Roman(600));
		w.EndPage();
	}
}
