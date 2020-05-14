#pragma once
#include <cstddef>
#include <string>
#include <assert.h>   
//Some basic components
//KEEP PADDING & ALIGMENT IN MIND
namespace ECS1 {
	// namespace Components {

	struct Position2D {
		int X, Y, Z;
		void Set(int x, int y, int z) {
			X = x;
			Y = y;
			Z = z;

		}
	};
	//you could also do a SoA (structure of arrays)
	//struct Position2DSOA {
	//array x
	//array y
	//array z

	template <typename Component>
	class ComponentContainer {
	private:
		std::size_t nrOfElements;
		std::size_t maxSize;
		Component* internalArray;

		std::string description;
		//currently we'll use a raw fixed size array ourself, the idea here ofcourse is that we can swap this out later if needs be, or we can base our other containers off of this

	public:
		ComponentContainer() = delete;
		ComponentContainer(std::size_t maxSize) :maxSize(maxSize) {
			internalArray = new Component[maxSize];
		}
		~ComponentContainer() {
			delete[] internalArray;
		}

		ComponentContainer(const ComponentContainer& cc) = delete; //for this you'd need a set and a get
		ComponentContainer(const ComponentContainer&& cc) = delete;
		//to do: assingment operators
		//int Set(const Component c) {

		//}
		int Add() {

			//noop in Release
			assert("Container full: " , nrOfElements <= maxSize, );

			//Component->Set();
			nrOfElements++;
		}
		int Remove(Component index) {
			/*we're putting a temp variable on the stack to facilitate
			swapping the to-be-removed element in the array with the last valid element in the array and
			then diminish the count of the existing elements*/
			Component temp = internalArray[nrOfElements];
			std::size_t lastPosition = nrOfElements - 1;

		}
		template <class ... Args>
		void Set(Args... args) {
			int currentInsertPos = nrOfElements;
			//insert on nrOfElements, index of the next 'free' component
			internalArray[currentInsertPos].Set(std::forward<Args>(args)...);
			nrOfElements++;

		}
		//overload square brackets/index operator
		Component& operator [](int index) {
			return internalArray[index];
		}
		std::size_t SizeInBytes() {
			return nrOfElements;
		}

	};
}

