#include <iostream>
#include <variant>

using namespace std;

// Define shapes
class Derived1 {
    public:
        void print() const { cout << "Derived1 Function" << endl; }
};

class Derived2 {
    public:
        void print() const { cout << "Derived2 Function" << endl; }
};

int main() {
    // Variant
    variant<Derived1, Derived2> var;

    // Lambda to call the method
    auto caller = [] (const auto& obj) { obj.print(); };

    // Visit
    visit( caller, var );

    return 0;
}
