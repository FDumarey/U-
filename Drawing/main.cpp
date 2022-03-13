#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct MyApp : TopWindow {
	virtual void Paint(Draw& w) override {
		w.DrawRect(GetSize(), White());
		w.DrawRect(10,10,60,80,Green());
		
		w.DrawLine(100,10,60,80,4,Green());
		
		w.DrawEllipse(310,20,80,60,LtBlue(),5,Red());
		
		w.DrawArc(RectC(410,20,80,60),Point(10,10),Point(450,80),3,Cyan());
		
		Vector<Point> p;
		p << Point(30,110) << Point(60,180) << Point(10,150) << Point(30,110);
		w.DrawPolygon(p,Blue());
		w.DrawPolyline(p,4,Black());
		
		w.DrawImage(40,240, CtrlImg::save());
		w.DrawImage(220,330,80,80,CtrlImg::save(),Blue());
		
		w.DrawText(20,330,"Hello World!",Arial(50).Bold());
		w.DrawText(320,380,400, "Hello World!", Courier(100).Underline());
	}
};

GUI_APP_MAIN
{
	MyApp().Sizeable().Run();
}
