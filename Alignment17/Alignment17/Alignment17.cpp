// Alignment17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <malloc.h>
#include <cstdlib>
#include <new>
//!!! alignas: this is supposed to work but isn't reliable for MSVC 19 compiler
//CORRECTION: make sure the correct language is selected
class alignas(32) Vec3d {

    double x, y, z;
};


int main()
{
    //changes between 8 and 16 in msvc env when you switch between 32 and 64bit
    std::cout << "__STDCPP_DEFAULT_NEW_ALIGNMENT__ is "
        << __STDCPP_DEFAULT_NEW_ALIGNMENT__ << std::endl;


    std::cout << "sizeof(Vec3d) is " << sizeof(Vec3d) << '\n';
    std::cout << "alignof(Vec3d) is " << alignof(Vec3d) << '\n';

    auto Vec = Vec3d{};
    auto pVec = new Vec3d[10];

    if (reinterpret_cast<uintptr_t>(&Vec) % alignof(Vec3d) == 0)
        std::cout << "Vec is aligned to alignof(Vec3d)!\n";
    else
        std::cout << "Vec is not aligned to alignof(Vec3d)!\n";

    if (reinterpret_cast<uintptr_t>(pVec) % alignof(Vec3d) == 0)
        std::cout << "pVec is aligned to alignof(Vec3d)!\n";
    else
        std::cout << "pVec is not aligned to alignof(Vec3d)!\n";

    delete[] pVec;

    //everything underneath is a bit messt, try to avoid this
    //int* pAlignedInt = new(std::align_val_t{ 64 }) int[10];
    //::operator delete(pAlignedInt, std::align_val_t{ 64 });

    ////with type
    //auto pAlignedType = new(std::align_val_t{ 32 }) MyType;
    //pAlignedType->~MyType();
    //::operator delete(pAlignedType, std::align_val_t{ 32 });
}

// 2GOOD RESOURCES:
//https://www.bfilipek.com/2019/08/newnew-align.html (where this came form)
//https://github.com/Twon/Alignment/blob/master/docs/alignment_in_C%2B%2B.md