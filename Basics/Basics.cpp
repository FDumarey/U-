#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	// 1.1 Log or dump commands
	int x = 123;
	LOG("Value of x is " << x);
	DUMPHEX(x);
	
	VectorMap<int, String> map = { {1, "one"}, {2, "two"}};
	DUMPM(map);
	
	//use RLOG for LOGS in release mode
	//use DLOG for LOGS in debug mode
	
	// 1.2 String
	String a = "Hello";
	a = a + " world";
	DUMP(a);
	a.Clear();
	for (int i=0; i<10; i++)
		a << i << ", "; // << operator add to strings number or chars
	DUMP(a);
	DUMP(a.GetLength());
	a.Insert(6, "<inserted>");
	DUMP(a);
	a.Remove(2,2);
	DUMP(a);
	DUMP(a.Find("e"));
	DUMP(a.ReverseFind("e"));
	DUMP(a.StartsWith("test"));
	DUMP(a.Mid(3,3));
	a.Trim(5);
	DUMP(a);
	DUMP(a[0]);
	for (char ch:a)
		LOG(ch);
	
	// 1.3 Stringbuffer for API calls that need a *char argument
	StringBuffer b;
	b.SetLength(200);
	strcpy(b, "Hello");
	b.Strlen();
	String y = b;
	DUMP(y);
	
	// 1.4 WString
	WString c = "characters 200-300: ";
	for (int i=200; i<300; i++)
		c.Cat(i);
	DUMP(c);
	String d = c.ToString();
	DUMP(d);
	WString e = d.ToWString();
	DUMP(e);
	
	// 1.5 Date and time
	Date date = GetSysDate();
	DUMP(date);
	DUMP((int)date.year);
	Time time = GetSysTime();
	DUMP(time);
	DUMP((int)time.hour);
	
	// 1.6 AsString, ToString, <<
	
	// 1.7 CombineHash
	struct foo
	{
		String a;
		int b;
		unsigned GetHashValue() const {return CombineHash(a,b);}
	};
	foo f;
	f.a = "world";
	f.b = 22;
	DUMP(GetHashValue(f));
	
	// 1.8 SgnCompare, CombineCompare
	int g=1;
	int h=2;
	DUMP(SgnCompare(g,h));
	struct foo4 : Comparable<foo4>
	{
		String a;
		int b;
		int c;
		int Compare(const foo4& x) const {return CombineCompare(a, x.a)(b, x.b)(c, x.c);}
	};
	foo4 o,p;
	o.a = "A";
	o.b = 1;
	o.c = 2;
	p.a = "A";
	p.b = 1;
	p.c = 3;
	DUMP(o<p);
	DUMP(o==p);
	
}
