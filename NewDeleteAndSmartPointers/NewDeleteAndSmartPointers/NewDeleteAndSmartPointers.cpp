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
	void PrintID() {
		std::cout << "I'm object" << ObjNr;
	}
};

void CheckWeakPointerExpired(std::weak_ptr<SomeObject>& wPtr0);

int main()
{
	//create a scope

	{
		//both work
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

	{
	//unique pointer (explicit ctor)
	std::unique_ptr<SomeObject> uPtrSomeObject(new SomeObject());
	//with make unique method - safer - if c'tor throws exception you won't end up with a dangling pointer with no reference
	std::unique_ptr<SomeObject> uPtrSomeObject2 = std::make_unique<SomeObject>();
	uPtrSomeObject->PrintID();
	}

	//shared ptr, reference counting mechanism
	//allocates another block: the 'control block' used for reference counting
	{
		std::shared_ptr<SomeObject> sPtr0;
		{

		std::shared_ptr<SomeObject> sPtr1 = std::make_shared<SomeObject>();
		sPtr0 = sPtr1;
		}

	} //will be destroyed here

	//	//weak ptr, doesn't add to 'count' when ref counting
	//
	{
		std::weak_ptr<SomeObject> wPtr0;
		{

			std::shared_ptr<SomeObject> sPtr1 = std::make_shared<SomeObject>();
			wPtr0 = sPtr1;
			CheckWeakPointerExpired(wPtr0);
		} //will be destroyed here
		CheckWeakPointerExpired(wPtr0);
	}
	std::cin.get();



}

void CheckWeakPointerExpired(std::weak_ptr<SomeObject>& ptr)
{
	//check if expired
	if (!ptr.expired()) {
		std::cout << "pointer is valid\n";
	}
	else {
		std::cout << "pointer  is expired\n";
	}
}
