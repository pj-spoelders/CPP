// MoveSem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MoveSem.h"
#include <utility>

class Test {
public:
    void DoSomething() {
        std::cout << "woot" << std::endl;
    }

    Test(int i):m_i(i) {

    }
    ~Test() {

    }

    Test(const Test& t) {
        m_i = t.m_i;
    }

    Test(Test&& t) {
        m_i = t.m_i;
    }
    //The copy assignment operator differs from the copy constructor in that it must clean up the data members of the assignment's target (and correctly handle self-assignment) whereas the copy constructor assigns values to uninitialized data members
    // could be = default; here
    Test& operator=(const Test& t) {
        this->m_i = t.m_i;
        return *this;
    }
    //move assignment operator, could be = default; here
    Test& operator=(Test&& t) {
        this->m_i = t.m_i;
        return *this;
    }


private:
    int m_i = 0;
};
//see page 627 C++ Primer
class DerivedTest : public Test {
    DerivedTest(int i) :Test(i) { //if you don't specify this the base default constructor would be called

    }
    ~DerivedTest() {

    }

    DerivedTest(const DerivedTest& t): Test(t) {

    }

    DerivedTest(DerivedTest&& t): Test(std::move(t)) {

    }

    DerivedTest& operator=(const DerivedTest& t) {
        Test::operator=(t);
        return *this;
    }

    DerivedTest& operator=(DerivedTest&& t) {
        Test::operator=(t);
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
    Test t(5);
    std::cout << "Hello World!\n";
    Test t2(666);
    t = t2;
    t.DoSomething();
    //std::move()
}

