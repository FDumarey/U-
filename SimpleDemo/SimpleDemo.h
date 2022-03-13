#ifndef _SimpleDemo_SimpleDemo_h
#define _SimpleDemo_SimpleDemo_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <SimpleDemo/SimpleDemo.lay>
#include <CtrlCore/lay.h>

class SimpleDemo : public WithSimpleDemoLayout<TopWindow> {
	void AddItem(); // Added a private function
public:
	typedef SimpleDemo CLASSNAME; // Needed for the THISBACK callback macro
	SimpleDemo();
};

#endif
