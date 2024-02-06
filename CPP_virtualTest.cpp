#include <iostream>
using namespace std;

class Base {
   public:
    virtual void print() {
        cout << "Base Function" << endl;
    }
};

class Derived1 : public Base {
   public:
    void print() {
        cout << "Derived1 Function" << endl;
    }
};

class Derived2 : public Base {
   public:
    void print() {
        cout << "Derived2 Function" << endl;
    }
};

int main() {
    Derived1 derived1;
    Derived2 derived2;

    // pointer of Base type that points to derived1
    Base* base1 = &derived1;
    Base* base2 = &derived2;

    // calls member function of Derived class
    base1->print();
    base2->print();

    return 0;
}