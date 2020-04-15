// StringsVectorsArrays.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "StringsVectorsArrays.h"

int main()
{
    //StringVectorsAndIterators();

    //ARRAYS

    //STACK
    int arr[3] = { 3,4,5 };
    std::cout << arr[0] << std::endl;;
    //
    //array of pointers to int
    int* pointerToIntArr[3]{ &arr[0], &arr[1],&arr[2] };
    std::cout << *pointerToIntArr[0] << std::endl;;

    //HEAP
    int* ptrToArr = new int[2]{ 1, 2 };
    std::cout << ptrToArr[0] << std::endl;
    //ptr to an array of pointers
    int** ppArr = new int* [2]{ &ptrToArr[0],&ptrToArr[0] };
    std::cout << *ppArr[0] << std::endl;

    delete[] ptrToArr;
    delete[] ppArr;

    //std array
    std::array<int, 3> stdArr;

    //pointers are iterators
    int* ptr = arr;
    std::cout << *++ptr << std::endl;
    std::cout << *++ptr << std::endl;
    std::cout << *++ptr << std::endl; //undefined!!!
    //C++ 11 - returns pointers 
    std::begin(arr);
    std::end(arr);

    //pointer arithmetic
    //subscript and pointers


    //"MULTIDIMENSIONAL ARRAYS


}

void StringVectorsAndIterators()
{
    std::string name;
    while (name.empty())
    {
        std::cout << "Please, enter your full name: ";
        std::getline(std::cin, name);
    }
    std::cout << "Hello, " << name << "!\n";
    //C11: RANGE FOR
    for (char c : name) {
        std::cout << c << std::endl;
    }
    for (char& c : name) {
        c = std::toupper(c);
    }
    std::cout << "Hello, " << name << "!\n";

    //accessing some chars
    //subscript operator []
    std::cout << "Starts with" << name[0] << std::endl;

    //VECTOR
    //SUBSCRIPT operator
    std::vector<std::string> vecStr{ "a","b","c","d","e","f" };
    for (int i = 0; i < vecStr.size(); i++) {
        std::cout << vecStr[i] << std::endl;
        vecStr[i].empty();
    }
    //ITERATOR
    for (auto it = vecStr.begin(); it < vecStr.end(); it++) {
        std::cout << *it << std::endl;
        //the parentheses apply the dereference operator to the iterator before applying the dot operator
        (*it).empty();
        //this is the same thing, uses the arrow operator (combines dereference and 
        it->empty();

    }
    //iterator arithmetic : pos 2
    std::vector<std::string>::iterator custIt = vecStr.begin() + 2;

    //!! iterator end
    std::vector<std::string>::iterator endIt = vecStr.end();
    //std::cout << *endIt << std::endl; //BOOM, this is one element past the last "element"
}
