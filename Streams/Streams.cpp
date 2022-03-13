#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	// 2.1 Streams basic
	FileOut out("test.txt");
	if (!out) 
	{ 
		LOG("Failed to open the file");
		return;
	}
	out << "Some number: " << 321 << " and point: " << Point(1,2);
	out.Close();
	
	FileIn in("test.txt");
	if (!in)
	{
		LOG("Failed to open the file");
		return;
	}
	in.Seek(0);
	DDUMP((char)in.Peek());
	DDUMP(in.GetLine());
	in.Seek(0);
	DUMP(in.Get(10));
	in.Close();
	
	FileAppend out2("test.txt");
	out2 << "\nSome more text";
	out2.Close();
	DUMP(LoadFile("test.txt"));
	
	StringStream ss;
	ss.Put32le(0x12345678);
	ss.Put32be(0x12345678);
	DUMPHEX(ss.GetResult());
	
	// 2.2 Special streams
	SizeStream szs;
	szs << "1234567";
	DUMP(szs.GetSize());
	
	StringStream sin("123456");
	CompareStream cs(sin);
	cs.Put("12345");
	DUMP(cs.IsEqual());
	TeeStream tee(sin, sin); //sends to two streams at the same time
	tee << "Test tee stream";
	tee.Close();
	DUMP(sin.GetResult());
	
	// 2.3 Serialization
	StringStream ss3;
	int x = 123;
	Color h = White();
	ss3 % x % h; //% = Serialize function
	StringStream ss4(ss3.GetResult());
	int x2;
	Color h2;
	ss4 % x2 % h2;
	DUMP(x2);
	DUMP(h2);
	
	struct foo
	{
		int number;
		Color color;
		void Serialize (Stream& s)
		{
			s % number % color;
		}
	};
	foo Myfoo;
	Myfoo.number = 321;
	Myfoo.color = Blue();
	String data = StoreAsString(Myfoo); //also StoreAsFile
	foo Myfoo2;
	LoadFromString(Myfoo2, data); //also LoadFromFile
	DUMP(Myfoo2.number);
	DUMP(Myfoo2.color);
	
	
}
