// GettingStarted.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

void DoStuff(int& iPtr) {
    std::cout << iPtr << std::endl;;
}
int main()

{
    //you can't do this, makes sense,why would you
    //int& refA = 42;
    //but you can do this? but what's the point & why?
    const int& refS = 42;
    std::cout << refS;

    int iVal = 0x11;
    
    int& iValRef = iVal;
    
    int* iPtr = &iVal;

    std::cout << iVal << "-" << iValRef << std::endl;
    DoStuff(iVal);
    DoStuff(*iPtr);

    iPtr = &iValRef;
    DoStuff(*iPtr);


    //nullptr 
     //older style:
    //NULL or à
    //iPtr = nullptr;

    //read access violation
    //DoStuff(*iPtr);

    //reference to a pointer 

    int*& refToPt = iPtr;

    const int* ptrToConst;//pointer to const
    int* const constPtrToInt = &iVal;//const pointer
    const int* const constPtrToConstInt = &iVal; // const pointer to const value
}


