#include <iostream>
using namespace std;

class Particle {
    public:
        virtual void print() const { cout << "Particle Function" << endl; }
};

class Sphere : public Particle {
    public:
        void print() const { cout << "Sphere Function" << endl; }
};

class Box : public Particle {
    public:
        void print() const { cout << "Box Function" << endl; }
};

void printClass( const Particle& Particle )
{
    Particle.print();
};

int main() {
    // pointer of Particle type that points to a Sphere or Box obj
    Particle* Particle1 = new Sphere();
    Particle* Particle2 = new Box();

    // calls member function of Derived class
    printClass( *Particle1 );
    printClass( *Particle2 );

    return 0;
}