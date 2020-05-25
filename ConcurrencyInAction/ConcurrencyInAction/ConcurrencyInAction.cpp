// ConcurrencyInAction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <thread>
#include <future>

#include <chrono>

#include "CreateThreads.h"
#include "ThreadGuard.h"


void WS() {
	std::cout << "--------------" << std::endl;
}
void fBV(std::string val) {
	val += " copy by value";
	std::cout << val << std::endl;
}
void fBR(std::string& val) {
	val += " pass by  ref";
	std::cout << val << std::endl;
}
void fBP(std::string* val) {
	*val += " pass by ptr";
	std::cout << *val << std::endl;
}
void PassingArgumentsToAThreadFunction() {
	std::string vV = "value -";
	auto mtv = std::thread(fBV, vV);
	mtv.join();
	std::cout << vV << std::endl;
	WS();
	//you can't even do this anymore withoutd std::ref so NP
	std::string vR = "value ref -";
	std::string& vRR = vR;
	auto mtr = std::thread(fBR, std::ref(vRR));
	mtr.join();
	std::cout << vR << std::endl;
	WS();

	std::string* vPtr = new std::string("value ptr -");
	auto mtp = std::thread(fBP, vPtr);
	mtp.join();
	std::cout << *vPtr << std::endl;
	WS();
}

//2.3
//scoped threat example, transfers thread to guard class with move

//class scoped_thread {
//	std::thread t;
//public:
//	scoped_thread(std::thread t) : 
//		t(std::move(t)) 
//	{
//		if (!t.joinable()) {
//			//throw std::logic_error("No thread");
//		}
//
//	}
//	~scoped_thread() {
//		if (t.joinable()) {
//			t.join();
//		}
//	}
//};

class scoped_thread
{
	std::thread t;
public:
	explicit scoped_thread(std::thread t_) :
		t(std::move(t_))
	{
		if (!t.joinable())
			throw std::logic_error("No thread");
	}
	~scoped_thread()
	{
		t.join();
	}
	scoped_thread(scoped_thread const&) = delete;
	scoped_thread& operator=(scoped_thread const&) = delete;
};

void calcalot(int val) {
	for (int i = 0; i <= 10000000; i++) {
		val += (val % 2) + (val / 2) + 1;
	}
	std::cout << "calcalot: " << val << std::endl;
}
int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

int main()
{
	//1
	CreateThreads();

	//2 THREAD GUARDS
	//keep exception safe code in mind so catch { .. join} in case you .join later
	//or use a RAII-principle thread guard as the author suggests
	//this isn't really needed for detach since you can execute that staement immediately
	ThreadGuard();

	//2.3
	PassingArgumentsToAThreadFunction();
	auto t11 =std::thread{ func(10) };
	t11.join();

	WS();
	//scoped_thread t(std::thread( calcalot,10) );
	scoped_thread t(std::thread(calcalot,10));
	scoped_thread tFunctor(std::thread{ func(10) });
	
	//check out if you can still pass a non temporary this way
	//std::thread tstNonTemp = std::thread(calcalot, 20);
	//scoped_thread tNT(tstNonTemp);
	//YOU CAN'T so you'd need to move the name var, using std::move, and maybe change the ctr thread argument to thread&& as to make it more clear, but the author's intention was probably to always use it this way
	std::cout << "Hello" << std::endl;

	WS();
	//this is only a hint and might be 0 so plan for that

	std::cout << "hardware concurrency: " << std::thread::hardware_concurrency() << std::endl;

	//
	std::cout << "max size to enable true sharing: " << std::hardware_constructive_interference_size;/*: Maximum
		size in bytes of contiguous memory to promote true sharing */
	std::cout << "min size to avoid false sharing: " << std::hardware_destructive_interference_size; /*: Minimum
		offset in bytes between two objects to avoid false sharing*/

	//SLEEP
	using namespace std::chrono_literals;
	std::cout << "Hello waiter\n" << std::flush;
	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(2s);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;
	std::cout << "Waited " << elapsed.count() << " ms\n";
	WS();
	//you can get the RESULTS of the top level function ran in a thread through a PROMISE (or the exception if an exception occurred) 
	// or by modifying shared variables  which may require synchronization, see std::mutex and std::atomic)

	//PROMISE:

	//PACKAGED TASK

	//ASYNC
	std::future<int> answer = std::async(gcd, 123, 6);
	//do other stuff:
	std::cout << "smth smth" << std::endl;
	std::cout << answer.get() << std::endl;
	//auto status = answer.wait_for(0s);
	//status
	//Mutual exlusion

	/**/


}
