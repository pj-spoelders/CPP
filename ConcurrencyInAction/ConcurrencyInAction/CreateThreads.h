#pragma once
#include <thread>
void hello()
{
	std::cout << "Hello concurrent world" << std::endl;
}
void do_some_work() {
	std::cout << "Doing some worky work" << std::endl;
}
class background_task
{
public:
	void operator()() const //2d () is the arg list
	{
		//do_something();
		//do_something_else();
		std::cout << "Doing some work from ftor" << std::endl;
	}
};
void CreateThreads()
{
	//FUNCTION
	std::thread my_thread(hello);
	my_thread.join();

	//LAUNCHING A THREAD


	std::thread my_threadWithFunction(do_some_work);

	//FUNCTOR
	//std::thread works with any
	//callable type, so you can pass an instance of a class with a function call operator to the
	//std::thread constructor instead :



	background_task f;
	std::thread my_threadFunctorInstance(f);


	/*In this case, the supplied function object is copied into the storage belonging to the
	newly created thread of executionand invoked from there.It’s therefore essential that
	the copy behave equivalently to the original, or the result may not be what’s expected.
	One thing to consider when passing a function object to the thread constructor is
	to avoid what is dubbed “C++’s most vexing parse.” If you pass a temporary rather
	17 Basic thread management
	than a named variable, then the syntax can be the same as that of a function declara -
	tion, in which case the compiler interprets it as such, rather than an object definition.
	For example,*/
	//std::thread my_threadFunctorTemporaryIssue(background_task());
	/*declares a function my_thread that takes a single parameter(of type pointer to a func -
	tion taking no parameters and returning a background_task object) and returns a
	std::thread object, rather than launching a new thread.You can avoid this by nam -
	ing your function object as shown previously, by using an extra set of parentheses, or
	by using the new uniform initialization syntax, for example: */
	std::thread my_threadDoubleParenthese((background_task()));

	std::thread my_threadInitializerSyntax{ background_task() };

	//USING A LAMBDA
	std::thread my_threadL([] {
		std::cout << "lambdaing" << std::endl;
		//do_something();
		//do_something_else();
		});

	my_threadWithFunction.join();
	my_threadFunctorInstance.join();
	my_threadDoubleParenthese.join();
	my_threadInitializerSyntax.join();
	my_threadL.join();

	//JOIN DISCARD AND THREAD GUARD
	//you need to join or detach or std::abort will get triggered
}