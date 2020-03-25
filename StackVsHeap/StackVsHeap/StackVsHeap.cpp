// StackVsHeap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
struct Vector3 {
    float x, y, z;
};

int main()
{

    //STACK
    int value = 5;

    int array[5];
    array[0] = 0;
    array[1] = 1;
    array[2] = 2;
    array[3] = 3;
    array[4] = 4;

    Vector3 vector();

    //HEAP

    int* valuePtr = new int;
    *valuePtr = 5;

    int* arrayPtr = new int[5];
        arrayPtr[0] = 0;
        arrayPtr[1] = 1;
        arrayPtr[2] = 2;
        arrayPtr[3] = 3;
        arrayPtr[4] = 4;

    Vector3* vectorPtr = new Vector3();


    delete valuePtr;
    delete[] arrayPtr;
    delete vectorPtr;

}

