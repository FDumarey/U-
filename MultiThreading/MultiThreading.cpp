#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	// 7.1 Threads
	Thread t;
	t.Run([] {
		for (int i=0; i<10; i++) {
		LOG("In the thread " << i);
		Sleep(100);
		}
		LOG("Thread is ending...");
		});
		
	for(int i=0; i<5; i++)
	{
		LOG("In the main thread " << i);
		Sleep(100);
	}
	LOG("Waiting for thread to finish...");
	t.Wait();
	LOG("All threads finished");
	
	// 7.2 Mutex
	Thread t2;
	Mutex m;
	int sum=0;
	t2.Run([&sum, &m]
	{
		for(int i=0; i<100000; i++)
		{
			m.Enter(); // Locks mutex m
			sum++;
			m.Leave(); // Unlocks mutex m
		}
		});
	
	for(int i=0; i<100000;i++)
	{
		Mutex::Lock __(m); //helper class to lock until the end of scope
		sum++;
	}
	
	t2.Wait();
	DUMP(sum);
	
	// 7.3 ConditionVariable
	bool stop = false;
	BiVector<int> data;
	Mutex mu;
	ConditionVariable cv; //variable to control thread flow
	
	Thread th;
	th.Run([&stop, &data, &mu, &cv]
	{
		Mutex::Lock __(mu);
		for (;;)
		{
			while(data.GetCount())
			{
				int q = data.PopTail();
				LOG("Data received: " << q);
			}
			if (stop)
				break;
			cv.Wait(mu); //wait for condition bound to mutex mu
		}
	});
	
	for (int i=0; i<10; i++)
	{
		{
			Mutex::Lock __(mu);
			data.AddHead(i);
		}
		cv.Signal(); //signals the conditionvariable, so thread is awakened
		Sleep(1);
	}
	stop = true;
	cv.Signal(); //awaken thread
	t.Wait(); //wait for thread to finish
	
	// 7.4 CoWork
	// used for multithreading app to distribute over multiple cores
	// uses worker threads for a function
	long lSum;
	int iLoop;
	Mutex mCowork;
	CoWork co;
	
	for (iLoop=0; iLoop < 10; iLoop++)
	{
		co & [&lSum, &mCowork] // starts a new thread from the worker threads
		{
			if(CoWork::IsCanceled()) // Check if the whole CoWork has been canceled
			{
				LOG("Job was canceled");
				return;
			}
			Mutex::Lock __(mCowork); // using a mutex to protect variable
			// CoWork::FinLock(); // replaces the mutex, locked till end of job
			for (int i=0; i<99000;i++)
				lSum += i;
		};
	}
	co.Finish(); // wait for all worker threads to be finished
	co.Cancel(); // cancel all worker threads, running ones will execute until ended
	DUMP(lSum);
	
	// 7.5 AsyncWork
	// Do in parallel with current thread
	auto a = Async([] (int n) -> double {
		double f=1;
		for(int i=2;i<=n;i++)
			f *= i;
		return f;
	}, 100);
	
	DUMP(a.Get()); // Get method waits for async thread to be finished
	
	// 7.6 CoPartition
	// Parallel processing
	int isum=0;
	Vector<int> vdata;
	for(int i=0;i<10000;i++)
		vdata.Add(i);
	CoPartition(vdata, [&isum](const auto& subrange) { // Parallel processing of arrays using a subrange
		int partial_sum=0;
		for(const auto& x : subrange)
			partial_sum += x;
		CoWork::FinLock(); // CoPartition inherits CoWork so available method
		isum += partial_sum;
	});
	DUMP(isum);
	
	// 7.7 CoDo
	// Job is started in all threads, code does the scheduling
	// Alternative to CoPartition
	Vector<String> sdata;
	for (int i=0; i<100; i++)
		sdata.Add(AsString(1.0/i));
	double dsum=0;
	
	std::atomic<int> ii(0); //atomic variable, defined behavior when multiple threads write and read at the same time
	
	CoDo([&] {
		double m=0;
		for (int i=ii++; i < sdata.GetCount(); i=ii++)
			m += atof(sdata[i]);
		CoWork::FinLock();
		dsum += m;
	});
	DUMP(dsum);
	
	// 7.8 Parallel algorithms
	// FindIndex -> CoFindIndex
	// Sort -> CoSort
	Vector<String> x {"zero", "one", "two", "three", "four", "five", "six", "seven"};
	DUMP(FindIndex(x, "two"));
	DUMP(CoFindIndex(x, "two"));
	CoSort(x);
	DUMP(x);
	
	
}
