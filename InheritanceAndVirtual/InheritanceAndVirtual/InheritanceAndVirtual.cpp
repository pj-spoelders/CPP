// InheritanceAndVirtual.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
class CtorDemo {
public:    
    CtorDemo() {
        std::cout << "Constructing base class" << std::endl;
    }
    ~CtorDemo() {
        std::cout << "Destroying base class" << std::endl;
    }
};
class CtorDemoDerived : public CtorDemo {
public:
    CtorDemoDerived() : CtorDemo()
    {
        std::cout << "Constructing derived class" << std::endl;
    }
    ~CtorDemoDerived() {
        std::cout << "Destroying derived class" << std::endl;
    }
};


//CTORS & DTORS ORDER (INHERITANCE)
class Entity {
public:

    virtual std::string GetName() {
        return "Entity";
    }

    Entity() {
        std::cout << "Constructing entity class" << std::endl;
    }
    virtual ~Entity() {
        std::cout << "Destroying entity class" << std::endl;
    }
};

class DerivedEntity : public Entity {
public:
    std::string  GetName() override {
        return "DerivedEntity";
    }


    DerivedEntity() {
        std::cout << "Constructing derived entity class" << std::endl;
    }
    ~DerivedEntity() {
        std::cout << "Destroying derived entity class" << std::endl;
    }

};

//PURE VIRTUAL / abstract class
class AbstractEntity {
public:
    virtual void DoSomething() = 0;
};

int main()
{
    //CTORS & DTORS ORDER (INHERITANCE)
    {
        CtorDemoDerived cdd;
    }

    //VIRTUAL/POLYMORFISM
    std::cout << "-------------" << std::endl;


        Entity* entityPtr0 = new Entity();
        //also demonstrates polymorfism
        //!!! BE VERY CAREFUL HERE, YOU NEED A VIRTUAL DESTRUCTOR, otherwise only the base dtor will be called and you'll experience a possible memory leak
        Entity* entityPtr1 = new DerivedEntity();

        std::cout << "-------------" << std::endl;

        std::cout << entityPtr0->GetName() << std::endl;
        std::cout << entityPtr1->GetName() << std::endl;
    
        std::cout << "-------------" << std::endl;

        delete entityPtr0;
        //!!! BE VERY CAREFUL HERE, YOU NEED A VIRTUAL DESTRUCTOR, otherwise only the base dtor will be called and you'll experience a possible memory leak
        delete entityPtr1;

    //pure virtual/abstract class : can't initialize/instantiate an object of this class
    //AbstractEntity ai;

}



