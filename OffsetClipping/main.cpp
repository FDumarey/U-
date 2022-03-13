#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct MyApp : TopWindow{
	void DoPainting(Draw& w) {
		w.DrawEllipse(0,0,100,30,WhiteGray(),1,Cyan);
		w.DrawText(0,0,"Hello World!", Roman(30).Bold());
	}
	
	virtual void Paint(Draw& w) override {
		w.DrawRect(GetSize(),White());
		DoPainting(w);
		
		w.Offset(30,50);
		DoPainting(w);
		w.End(); // Return to previous state
		
		w.Offset(20,100);
		w.Clip(5,5,40,20);
		DoPainting(w);
		w.End(); // Returns to offset
		w.End(); // Returns to normal
		w.Clipoff(10,150,60,20);
		DoPainting(w);
		w.End();
	}
};

GUI_APP_MAIN
{
	MyApp().Sizeable().Run();
}
