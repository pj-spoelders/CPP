

//#include "ProblemPolymorfism.h"
#include <iostream>
#include <string>

void WL(std::string s) {
	std::cout << s << std::endl;
}
void WS() {
	WL("------------------------");
}

#include <vector>
class TestClass {
public:
	TestClass() {
		WL("Ctor");
	}
	TestClass(int i, int b) {
		WL("Ctor (with params)");
	}
	~TestClass() {
		WL("dtor");
	}
	TestClass(const TestClass& tc) {
		WL("Copy Ctor");
	}
	TestClass(TestClass&& tc) {
		WL("Move Ctor");
	}
	TestClass& operator=(const TestClass& tc) {
		WL("Copy Assignment Op");
	}
	TestClass& operator=(TestClass&& tc) {
		WL("Move Assignment Op");
	}
};
void TestMethodC(TestClass& tc) {
	TestClass tcM = tc;
}
void TestMethodC(TestClass&& tc) {
	TestClass tcM = std::move(tc);
}
void TestMethodM(TestClass&& tc) {
	TestClass tcM = tc;
}
void TestClassF() {

}

//https://en.cppreference.com/w/cpp/container/vector/emplace_back

TestClass createTestClass() {

	return TestClass();
}
int main()
{

	//Problem1
	//PolymorfismPrefixPostfixAndUniquePtr();

	//argument forwarding + construction
	std::vector<TestClass> vecTestClass;

	//TO SOLVE ALL THE Copty Ctors Firing we'll just reserve some space here
	vecTestClass.reserve(20);

	//forwards arguments and then uses placement new internally
	WS();
	WL("Parameterless emplace back:");
	vecTestClass.emplace_back();
	WS();
	WL("emplace back with parameters:");
	//https://zpjiang.me/2018/08/08/Copy-Constructor-and-std-vector-emplace-back/ I Had a copy happening here, vector resizes itself leading to a copy of the first 1 element
	vecTestClass.emplace_back(1, 2); //the compiler stops you from doing stupid stuff with this
	WS();
	WL("Push back Creating new instance of class using Ctor");
	//move or copy
	
	vecTestClass.push_back(TestClass()); //same here 

	WS();
	WL("");
	//this 'll do a copy ctor 
	TestClass tc1;
	WS();
	vecTestClass.push_back(tc1);
	WS();
	WL("return function:");
	//see what this does with a helperfunction
		//it does RVO and then it moves
	vecTestClass.push_back(createTestClass());
	WS();



	TestClass tc;

	TestClass tc2;
	TestClass&& tcMoved = std::move(tc2);
	//doesn't work
	//TestMethodM(th);
	//you need to std::move it to convert it to an rvalue reference)
	WS();
	//it will still pick the reference/copy version, because you might still use it later on or (might change with a different compiler)
	TestMethodC(tcMoved);
	//
	WS();
	WL("This will move, the compiler gets this:");
	TestMethodC(TestClass());
	WS();
	WL("Foring with std::move");
	//unless you really force it to, like here,so the compiler knows what's up
	TestMethodC(std::move(tcMoved));
	WS();
	TestMethodC(std::move(TestClass()));
	WS();
	



}

