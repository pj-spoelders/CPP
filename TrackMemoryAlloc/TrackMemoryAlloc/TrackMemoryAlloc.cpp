// TrackMemoryAlloc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct AllocationMetrics {
    uint32_t TotalAllocated;
    uint32_t TotalFreed;

    uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics allocMetrics;
static void PrintMemoryUsage() {
    std::cout << "Current memory usage:" << allocMetrics.CurrentUsage() << "bytes" << std::endl;
}
//override new operator (globally)
void* operator new(size_t size) {
    allocMetrics.TotalAllocated += size;

    return malloc(size);
}
//void operator delete(void* memory) {
//    free(memory);
//}
// if you also need type information you can easily override the destructor this way
void operator delete(void* memory,size_t size)
{
    allocMetrics.TotalFreed += size;
    free(memory);
}
struct Object
{
    int x, y, z;
};
int main()
{
    PrintMemoryUsage();
    Object* objectPtr = new Object();
    PrintMemoryUsage();
    {
        std::unique_ptr<Object> obj = std::make_unique<Object>();
        PrintMemoryUsage();
    }
    std::string HelloStr = "Heya guys";
    PrintMemoryUsage();
    std::cout << "Hello World!\n";
    PrintMemoryUsage();
}
