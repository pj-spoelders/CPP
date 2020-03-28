// NewDeleteAndSmartPointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

struct SomeObject
{
	int ObjNr = 0;
	SomeObject() :ObjNr(9000) {
		std::cout << "Creating object " << this->ObjNr << std::endl;
	};

	SomeObject(int ObjNr) : ObjNr(ObjNr) {
		//this->ObjNr = ObjNr;
		std::cout << "Creating object " << this->ObjNr << std::endl;
	}

	~SomeObject() {
		std::cout << "Destroying object " << ObjNr << std::endl;
	}
};

int main()
{
	//create a scope
	{
		//try to avoid this, since it's not superclear
		SomeObject testObject(1337);
		SomeObject testObject2;

		SomeObject testObject3 = SomeObject(1337);

		SomeObject testObject4 = SomeObject();



	}
	//stack will unwind when going out of scope


	{
		std::vector<SomeObject*> someObjectVector = std::vector<SomeObject*>();
		for (int i = 0; i < 10000; i++) {
			int objectId = i + 1;
			someObjectVector.push_back(new SomeObject(objectId));

		}

		//memory leak if you don't delete!
		//someObjectVector.clear();

		//solution: delete or use smart pointers that manage scope
		//1. delete
		for (auto& o : someObjectVector) {
			delete o;
		}
		someObjectVector.clear();
	}

	{
		//2. smartpointer: unique
		std::vector<std::unique_ptr<SomeObject>> someObjectUniquePtrVector = std::vector<std::unique_ptr<SomeObject>>();
		for (int i = 0; i < 10000; i++) {
			int objectId = i + 1;
			someObjectUniquePtrVector.push_back(std::make_unique<SomeObject>(objectId));

		}
		someObjectUniquePtrVector.clear();
	}

	std::cin.get();



}
