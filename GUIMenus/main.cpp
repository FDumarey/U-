#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define IMAGECLASS ImagesImg //check class in image designer, right click image
#define IMAGEFILE <GUIMenus/images.iml> //package and file name of iml file
#include <Draw/iml.h>

struct MyAppWindow : TopWindow {
	MenuBar menu;
	ToolBar tool;
	StatusBar status;
	Button lt,rt,lb,rb,lv,ht,hv,cb,rc;
	
	typedef MyAppWindow CLASSNAME; // needed for THISFN macro
	
	void Exit() {
		if(PromptOKCancel("Exit MyApp?"))
			Break();
	}
	
	void SubMenu (Bar& bar){
		bar.Add("Exit", [=] { Exit(); }).Help("This invokes the Exit command"); //no image so only menu item, help = help text for status bar
		bar.Separator(); // both separator for menu and toolbar
		bar.Add("ExitImg", ImagesImg::ImgExit(), [=] { Exit(); }); //copy image from image designer object; toolbar & menu with tooltip
		bar.Separator(); // insert separator
		bar.Add(ImagesImg::ImgTool1(), [=] { Exit(); }).Help("This invokes the Fn1 toolbar command"); // no text, so only toolbar with icon
		bar.Add(ImagesImg::ImgTool2(), [=] { Exit(); }).Help("This invokes the Fn2 toolbar command");
	}
	
	void MainMenu (Bar& bar){
		bar.Sub("Menu", [=](Bar& bar) { SubMenu(bar); });
	}
	
	void RightDown(Point, dword) override {
		MenuBar::Execute([=](Bar& bar){bar.Add("Exit", [=]{Exit();}); // Context menu
		}
		);
	}
			
	MyAppWindow() {
		Title("My Application with menus").Sizeable();
		AddFrame(menu); // Top frame menu
		AddFrame(TopSeparatorFrame()); // Add a top separator frame
		AddFrame(tool); // Top frame toolbar
		AddFrame(status); // Add a Status bar
		AddFrame(InsetFrame()); // Add an inset frame
		menu.Set([=](Bar& bar){MainMenu(bar);});
		menu.WhenHelp = status; // sets the help text output to the status StatusBar object
		tool.Set([=](Bar& bar){SubMenu(bar);});
		tool.WhenHelp = status;
		
		*this
			<< lt.SetLabel("left-top").LeftPos(10,200).TopPos(10,40) // operator << = add action
			<< rt.SetLabel("right-top").RightPos(10,200).TopPos(10,40)
			<< lb.SetLabel("left-bottom").LeftPos(10,200).BottomPos(10,40)
			<< rb.SetLabel("right-bottom").RightPos(10,200).BottomPos(10,40)
			<< lv.SetLabel("left-vsize").LeftPos(10,200).VSizePos(60,60)
			<< ht.SetLabel("hsize-pos").HSizePos(220,220).TopPos(10,40)
			<< hv.SetLabel("hsize-vsize").HSizePos(220,220).VSizePos(60,60)
			<< cb.SetLabel("hcenter-bottom").HCenterPos(200).BottomPos(10,40)
			<< rc.SetLabel("right-vcenter").RightPos(10,200).VCenterPos(40);
	}
};

GUI_APP_MAIN
{
	MyAppWindow app;
	app.Run();
}
