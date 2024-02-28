/* README ----------------------------------------------------------------------
Compile with "g++ CPP_virtualTest.cpp -o virtualTest".
Run with "./virtualTest 1" for the Spherical particles
and      "./virtualTest 2" for the Box-shaped particles
----------------------------------------------------------------------------- */
#include <iostream>
#include <new>
using namespace std;

class Particle {
    public:
        virtual double computeVolume() const 
        { 
            cout << "computeVolume() is not defined for this type" << endl; 
            return( 0. );
        }
};

class Sphere : public Particle {
    private:
        double m_radius;
    public:
        Sphere( double rad )
        : m_radius( rad )
        {}

        double computeVolume() const 
        { 
            return( 3.1415 * m_radius * m_radius );
        };
};

class Box : public Particle {
    private:
        double m_extent;
    public:
        Box( double extent )
        : m_extent( extent )
        {}

        double computeVolume() const
        { 
            return( m_extent * m_extent * m_extent );
        }
};

void multiplyVolumeByTwo( Particle const& Particle )
{
    double tmp = 2. * Particle.computeVolume();
    cout << "Volume multiplied by two is " << tmp << "\n";
};

int main( int argc, char* argv[] ) 
{
    // BuilderFactory
    Particle* myParticle;
    switch ( stoi( argv[1] ) )
    {
    case ( 1 ):
        myParticle = new Sphere( 1. );
        break;
    case ( 2 ):
        myParticle = new Box( 1. );
        break;
    default:
        break;
    }

    // calls member function of Derived class
    multiplyVolumeByTwo( *myParticle );

    return 0;
}