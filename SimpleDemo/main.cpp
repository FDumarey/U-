#include "SimpleDemo.h"

SimpleDemo::SimpleDemo()
{
	CtrlLayout(*this, "Shopping List ©2021 FréSoft");
	Sizeable().Zoomable();
	arrList.AddColumn("Item");
	arrList.Removing(); // Gives possibility to remove an item from the arraylist
	btnAdd <<= THISBACK(AddItem); // link the function to the button using callback function
}

void SimpleDemo::AddItem()
{
	// The ~ operator calls the getdata function
	arrList.Add(~strItem);
	strItem <<= Null;
}

GUI_APP_MAIN
{
	SimpleDemo().Run();
}
