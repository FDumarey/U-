#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	// 4.1 Range
	Vector<int> x = {1,3,5,4,100,50,40};
	DUMP(SubRange(x,3,6));
	DUMP(ConstRange(1,10));
	DUMP(ReverseRange(x));
	DUMP(SortedRange(x));
	DUMP(FilterRange(x, [](int x) {return x > 30;}));
	
	// 4.2 Algorithms
	DUMP(FindIndex(x,5));
	DUMP(FindMin(x));
	DUMP(FindMax(x));
	DUMP(Min(x));
	DUMP(Max(x));
	DUMP(Count(x,100));
	DUMP(Sum(x));
	Sort(x); //use stablesort if equal values keeps original order at a performance penalty
	DUMP(x);
	DUMP(GetSortOrder(x)); //the order of items as sorted
	
}
