// MoveSem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MoveSem.h"
#include <utility>
#include <iostream>

void WriteLine(std::string s) {
    std::cout << s << std::endl;
}
void WriteSeparation() {
    WriteLine("-------------");
}
class Test {
public:
    void DoSomething() {
        std::cout << "woot" << std::endl;
    }

    Test(int i):m_i(i) {
        WriteLine("Base Class Constructor");
    }
    ~Test() {
        WriteLine("Base Class Destructor");
    }

    Test(const Test& t) {
        m_i = t.m_i;
        WriteLine("Base Class Copy Constructor");
    }

    Test(Test&& t) {
        WriteLine("Base Class Move Constructor");
        m_i = t.m_i;
    }
    //The copy assignment operator differs from the copy constructor in that it must clean up the data members of the assignment's target (and correctly handle self-assignment) whereas the copy constructor assigns values to uninitialized data members
    // could be = default; here
    Test& operator=(const Test& t) {
        this->m_i = t.m_i;
        WriteLine("Base Class Copy Assignment Operator");
        return *this;
    }
    //move assignment operator, could be = default; here
    Test& operator=(Test&& t) {
        this->m_i = t.m_i;
        WriteLine("Base Class Move Assignment Operator");
        return *this;
    }


private:
    int m_i = 0;
};
//see page 627 C++ Primer
class DerivedTest : public Test {
public:
    DerivedTest(int i) :Test(i) { //if you don't specify this the base default constructor would be called
        WriteLine("Derived Class Constructor");
    }
    ~DerivedTest() {
        WriteLine("Derived Class Destructor");
    }

    DerivedTest(const DerivedTest& t): Test(t) {
        WriteLine("Derived Class Copy Constructor");
    }
    //is this std::move necessary? investigate further when you've got nothing  to do
    //ANSWER: it is
    DerivedTest(DerivedTest&& t): Test(std::move(t)) {
        WriteLine("Derived Class Move Constructor");
    }

    DerivedTest& operator=(const DerivedTest& t) {
        WriteLine("Derived Class Copy Assignment Operator");
        Test::operator=(t);
        return *this;
    }

    DerivedTest& operator=(DerivedTest&& t) {
        WriteLine("Derived Class Move Assignment Operator");
        Test::operator=(std::move(t));
        return *this;
    }
};
//https://pspdfkit.com/blog/2019/when-cpp-doesnt-move/
class Lifetime {
public:
    Lifetime() { std::cout << "Constructor" << std::endl; }
    Lifetime(const Lifetime& other) {
        std::cout << "Copy Constructor" << std::endl;
    }
    Lifetime(Lifetime&& other) noexcept {
        std::cout << "Move Constructor" << std::endl;
    }
    Lifetime& operator=(const Lifetime& other) {
        std::cout << "Copy Assignment" << std::endl;
        return *this = Lifetime(other);
    }
    Lifetime& operator=(Lifetime&& other) noexcept {
        std::cout << "Move Assignment" << std::endl;
        return *this;
    }
};

Test createTest(int i) {
    Test temp(i);
        return temp;
}
int main()
{

    DerivedTest dt(1);
    WriteSeparation();
    //copy ctor
    DerivedTest dt2(dt);
    WriteSeparation();
    //move ctor
    DerivedTest dt3(std::move(dt2));
    WriteSeparation();
    //copy ctor (implicit)
    DerivedTest dt4 = dt3;
    WriteSeparation();
    //move ctor (implicit)
    DerivedTest dt5 = std::move(dt4);
    WriteSeparation();

 
    DerivedTest dt6(1337);
    DerivedTest dt7(9000);
    WriteSeparation();
    //copy assignment operator
    dt6 = dt7;
    WriteSeparation();
    //move assingment operator
    dt6 = std::move(dt7);
    WriteSeparation();
}

