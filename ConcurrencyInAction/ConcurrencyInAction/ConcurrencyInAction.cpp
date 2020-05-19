// ConcurrencyInAction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>

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
	std::cout << "Hello" << std::endl;

	WS();
	//this is only a hint and might be 0 so plan for that
	std::cout << "hardware concurrency: " << std::thread::hardware_concurrency() << std::endl;

}
