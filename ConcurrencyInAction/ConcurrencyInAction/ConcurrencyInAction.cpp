// ConcurrencyInAction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>

void hello()
{
    std::cout << "Hello concurrent world" << std::endl;
}
int main()
{

    std::thread my_thread(hello);
    my_thread.join();

    //LAUNCHING A THREAD
    void do_some_work();
    std::thread my_thread(do_some_work);

    //functor
    //std::thread works with any
    //callable type, so you can pass an instance of a class with a function call operator to the
    //std::thread constructor instead :
    class background_task
    {
    public:
        void operator()() const //2d () is the arg list
        {
            //do_something();
            //do_something_else();
        }
    };
    background_task f;
    std::thread my_thread(f);

    //using a lambda
    std::thread my_thread([]{
        std::cout << "lambdaing";
    //do_something();
    //do_something_else();
    });
}

