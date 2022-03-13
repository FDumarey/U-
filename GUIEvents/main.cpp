#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct MyAppWindow:TopWindow {
	Point p;
	String text;
	
	void Close() override {
		delete this; // delete this window
	}
	
	virtual void LeftDown(Point pos, dword flags) override {
		p=pos;
		Refresh();
		(new MyAppWindow)->OpenMain(); // Open new window on the heap
	}
	
	virtual void MouseMove(Point pos, dword flags) override {
		text = Format("[%d:%d]", pos.x, pos.y);
		Refresh();
	}
	
	virtual void Paint(Draw& w) override {
		w.DrawRect(GetSize(),White);
		w.DrawText(p.x, p.y, text, Arial(20), Magenta);
	}
	
	MyAppWindow() {
		Title("My Application").Zoomable().Sizeable();
		p.x=p.y=0;
	}
};

GUI_APP_MAIN
{
	(new MyAppWindow)->OpenMain();
	Ctrl::EventLoop(); // wait for all topwindows to be closed
}
