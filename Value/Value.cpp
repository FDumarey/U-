#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	// 5.1 Value
	Value a = 1;
	Value b = 2.34;
	Value c = GetSysDate();
	Value d = "Hello world!";
	DUMP(a.Is<int>());
	
	// 5.2 Null
	int x = Null;
	DUMP(x);
	
	// 5.3 Client types and Value, RawValue, RichValue
	// see reference guide
	
	// 5.4 ValueArray and ValueMap
	ValueArray va {1,2,3};
	DUMP(va);
	va.Add(10);
	va << 20 << 21;
	va.Set(0,999);
	DUMP(va);
	va.Remove(0,2);
	ValueArray v {100};
	va.Insert(1,v);
	DUMP(va);
	
	ValueMap m;
	m.Add("one", 1);
	DUMP(m);
	m.Add("two", 2);
	DUMP(m["two"]);
	LOG(m.GetKeys());
	m.Set("two", 4);
	m.SetKey(1, "four");
	DUMP(m);
	
}
