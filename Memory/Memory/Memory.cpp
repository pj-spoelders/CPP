// Memory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <stdint.h>
typedef uint32_t U32 ;

//https://eli.thegreenplace.net/2011/02/17/the-many-faces-of-operator-new-in-c
size_t allocationSizeBytes = 1024;
void* ptrAllocSpace = ::operator new(1024);//5 * sizeof(*v)));
//::operator delete(v); // this won't work on a void pointer

size_t currrentlyAllocatedSize = 0;

void* pointerToAllocatedMemory = ptrAllocSpace;

void* allocateUnaligned(size_t bytes) {
	currrentlyAllocatedSize += bytes;

		void* addressToReturn = pointerToAllocatedMemory;

		size_t currentPointerAddress = (int)pointerToAllocatedMemory;
		size_t newPointerAddress = currentPointerAddress + bytes;
		pointerToAllocatedMemory = (void*)newPointerAddress;
	return addressToReturn;
}


//Game engine architecture 5.2.1.3
void* allocateAligned(U32 size_bytes, U32 alignment) {
	//determine total amount of memory to allocate
	U32 expandedSize_Bytes = size_bytes + alignment;

	//allocate the unallocated memory block
	U32 rawAddress = (U32)allocateUnaligned(expandedSize_Bytes);
	
	U32 mask = (alignment - 1);
	U32 misalignment = (rawAddress & mask);
	U32 adjustment = alignment - misalignment;
	U32 alignedAddress = rawAddress + adjustment;
	return (void*)alignedAddress;
}
template <typename T>
void* allocateAlignedType() {
	
	return allocateAligned(sizeof(T), alignof(T));
}

int main()
{
	std::cout << sizeof(int) << std::endl;
	
	int* newI1 = new(allocateAlignedType<int>()) int;

	*newI1 = 9000;
	std::cout << *newI1 << std::endl;
	//::operator delete(ptrAllocSpace, 1024);
}

