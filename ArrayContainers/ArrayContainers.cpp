#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	// 3.1 Vector basics
	Vector<int> v;
	v.Add(1);
	DUMP(v);
	v << 4 << 5;
	v.Append({6, 7});
	for(int i=0; i < v.GetCount(); i++)
		LOG(v[i]);
	
	// 3.2 Vector operations
	v.Insert(2,10);
	v.Remove(0);
	DUMP(v);
	v.Get(13,-1); //gets first element in array, if not exists return second argument
	Sort(v);
	DUMP(v);
	
	// 3.3 Transfer issues
	Vector<int> v1;
	v1 = pick(v); //picks elements from v
	DUMP(v);
	DUMP(v1);
	v = clone(v1);
	DUMP(v);
	
	// 3.4 Client types
	struct Distribution : Moveable<Distribution>
	{
		String text;
		Vector<int> data;
		String ToString() const {return text + ": " + AsString(data); }
	};
	Vector<Distribution> dist;
	for(int n=5; n <= 10; n++)
	{
		Distribution& d= dist.Add();
		d.text << "Test" << n;
		for(int i=0; i<10000; i++)
			d.data.At(Random(n),0)++;
	}
	DUMPC(dist);
	
	// 3.5 Array flavor
	Array<std::string> as;
	as.Add("Test");
	for (auto s : as)
		DUMP(s.c_str());
	
	// 3.6 Polymorphic Array
	Array<Distribution> num;
	
	// 3.7 Bidirectional containers
	BiVector<int> n;
	n.AddHead(1);
	n.AddTail(100);
	DUMP(n);
	n.DropHead();
	DUMP(n);
	
	// 3.8 Index
	Index<String> ndx;
	ndx.Add("alfa");
	ndx.Add("beta");
	ndx.Add("gamma");
	ndx.Add("delta");
	ndx.Add("kappa");
	DUMP(ndx);
	DUMP(ndx.Find("beta"));
	ndx.Set(1,"alfa");
	DUMP(ndx);
	ndx.FindAdd("one"); //if not found add the element
	DUMP(ndx);
	ndx.Unlink(2); //not findable anymore
	DUMP(ndx.IsUnlinked(2));
	ndx.Put("foo");
	ndx.Sweep(); //remove unlinked elements
	DUMP(ndx);
	ndx.Remove(1);
	ndx.Insert(0,"new");
	DUMP(ndx);
	
	// 3.9 Index and client types
	// index types must be Moveable, Operator== and GetHashValue
	
	// 3.10 VectorMap, ArrayMap
	VectorMap<String, int> m;
	m.Add("A",1);
	m.Add("C",4);
	DUMP(m);
	DUMP(m.GetKeys());
	DUMP(m.GetValues());
	m.GetValues()[1] = 100;
	DUMP(m);
	DUMP(m.Find("C")); //finds key, findnext is available
	DUMP(m.Get("C")); // finds value for key
	m.SetKey(1, "D");
	
	// 3.11 One
	// like std::unique_ptr
	One<int> s;
	DUMP(bool(s)); //true if container has an element
	int *b = ~s; // ~ = gets pointer
	
	// 3.12 Any
	// container of any type for one element
	Any x;
	x.Create<String>() = "Hello";
	if (x.Is<String>()) 
		LOG("Any is now string: " << x.Get<String>());
	
	// 3.13 InVector, InArray
	// fast insert and remove operations (10x faster than Vector, Array)
	// but 10x slower on operator []
	
	// 3.14 SortedIndex, SortedVectorMap, SortedArrayMap
	// keeps all elements sorted
	
	// 3.15 Tuples
	// combines 2-4 values with different types
	Tuple<int, String, String> x2 = MakeTuple(12, "Hello", "world");
	DUMP(x2);
	int i1;
	String s1, s2;
	Tie(i1, s1, s2) = x2;
	DUMP(i1);
	DUMP(s1);
	DUMP(s2);
	
		
}
