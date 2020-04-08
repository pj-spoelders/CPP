// GettingStarted.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

void DoStuff(int& iPtr) {
    std::cout << iPtr << std::endl;;
}
int main()
{

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
}


