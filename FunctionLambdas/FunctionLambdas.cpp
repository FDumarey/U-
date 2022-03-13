#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	// 6.1 Function
	Function<int (int)> fn = [](int n) { LOG("Called A"); return 3*n; };
	int n=fn(7);
	DUMP(n);
	
	fn << [](int n) { LOG("Called B"); return n*n; };
	n = fn(7);
	DUMP(n);
	
	fn.Clear();
	n = fn(7);
	DUMP(n);
	
	Event<> ev = [] { LOG("Event invoked"); }; // event returns void
	ev();
	
	Gate<int> gt = [](int x) { LOG("Gate invoked with: " << x); return x < 10; }; // gate returns boolean
	bool b=gt(8);
	DUMP(b);
	
	// 6.2 U++ containers in lambdas
	Vector<int> x {1,2};
	Array<String> y {"one", "two"};
	Event<> ev2 = [x=pick(x), y=clone(y)] {DUMP(x); DUMP(y); };
	DUMP(x);
	DUMP(y);
	ev2();
	
}
