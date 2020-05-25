// StandardLibQuickRef.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
int main()
{
    std::cout << "Hello World!\n";

    std::vector<int> v{ 2,4,5,8,9 };
    std::for_each(v.begin(), v.end(), 
        [](auto& element) {std::cout << element << std::endl; });

    bool exists = std::any_of(v.begin(), v.end(), [](int i) { return i > 4; });
    
    std::cout << exists << std::endl;

    int nrToCompareTo = 10;
    bool existsWithState = std::any_of(v.begin(), v.end(), [nrToCompareTo](int i) { return i = nrToCompareTo; });

    std::cout << exists << std::endl;


    //Binary search: needs to be sorted before searching or undefined behaviour

    //generating
    std::vector<int> vec(6); // 0,0,0,0,0,0
    int value = 11;
    std::generate(begin(vec), begin(vec) + 3,
        [&value] { value *= 2; return value; }); // 22,44,88,0,0,0
    //std::iota(begin(vec) + 3, end(vec), 2); // 22,44,88,2,3,4


    std::vector<int> numbers{ 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };
    std::vector<int> evens(numbers.size());
    auto end = std::copy_if(cbegin(numbers), cend(numbers), begin(evens),
        [](int x) { return x % 2 == 0; });
    //returns iterator where it ended inserting
    //erase empty elements
    evens.erase(end, evens.end());

    std::vector<int> v2{ 3,4,4,4,5,6,4,5,5,7 };
    auto result = std::unique(std::begin(v2), std::end(v2));
    // possible outcome: 3,4,5,6,4,5,7,5,5,7
    v2.erase(result, std::end(v2));
}
