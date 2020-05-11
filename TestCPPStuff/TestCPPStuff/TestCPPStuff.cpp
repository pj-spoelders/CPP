// TestCPPStuff.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <utility>
struct Base {
	virtual void Drive() {
		std::cout << "vroom" << std::endl;
	}
};
struct DerivedClass :public Base{
	virtual void Drive() override {
		std::cout << "VRRR" << std::endl;
	}
};
struct DerivedDerivedClass: public DerivedClass {
	void Drive() override {
		std::cout << "BEEP BEEP" << std::endl;
	}
};
int main()
{
	//1.this was your first problem
	//polymorfism only works with pointers or references
	//ideally use a unique_ptr here instead of a 'raw' ptr like Winjerome mnetioned
	std::vector <Base*> vec;
	vec.emplace_back( new DerivedClass());
	vec.emplace_back( new DerivedDerivedClass());
	auto it = vec.begin();
	(*it)->Drive();//doesn't work
	//2. this is your second problem here; the postfix only gets executed after it already 'returned' its iterator so it's still pointing to element 0
	//(*it++)->Drive();
	//you could use the prefix version
	(*++it)->Drive();
	//our you could increment the iterator using the prefix or postfix version and then call Drive after you've done so to make it all a bit less confusing
	//it++;
	//*it)->Drive();

	//to prevent memory leaks you need to delete what you newed
	for (auto element : vec) {
		delete element;
	}

	//same thing with unique pointers
	std::vector <std::unique_ptr<Base>> vec2;
	vec2.emplace_back(std::make_unique<DerivedClass>());
	vec2.emplace_back(std::make_unique<DerivedDerivedClass>());
	auto it2 = vec2.begin();
	(*it2)->Drive();//doesn't work
	(*++it2)->Drive();

	//now I don't need to delete the elements myself manually since unique_ptr will do this once unique_ptr goes out of scope and gets destroyed

}

