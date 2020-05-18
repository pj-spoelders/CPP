#pragma once
#include <thread>

//contains reference to thread and in dtor will call .join when the tg object goes out of scope, bit like a unique_ptr
class thread_guard
{
private:
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) :
		t(t_)
	{}
	~thread_guard()
	{
		if (t.joinable())
		{
			t.join();
		}
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
	//since C++11 also disable 
	thread_guard(thread_guard const&&) = delete;
	thread_guard& operator=(thread_guard const&&) = delete;
};
struct func {
private:
	int ls;
public:
	func(int ls) {

	}
	void operator ()() {

	}
	

};
void fTG()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	//do_something_in_current_thread();
	//shit won
}