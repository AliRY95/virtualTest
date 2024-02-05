#include "hip/hip_runtime.h"
#include <iostream>

class Base
{
public:
    __device__ Base() {}
    __device__ virtual ~Base() {}
    __device__ virtual void Print() const = 0;
};

class Derived : public Base
{
private:
    int m_int;
public:
    __device__ Derived( int myInt ) : m_int( myInt ) {}

    __device__ ~Derived()
    {}

    __device__ void Print() const { printf( "my value is %d.\n", m_int ); }
};

__global__ void PrintClass( Base** __restrict__ Base )
{
    (*Base)->Print();
}

__global__ void create_base( Base** Base, int myInt )
{
    if (threadIdx.x == 0 && blockIdx.x == 0)
        (*Base) = new Derived( myInt );
}

__global__ void delete_base(Base** Base)
{
    delete *Base;
}

int main()
{
    // Create Base.
    Base** d_base;
    hipMalloc(&d_base, sizeof(Base**));
    create_base<<<1, 1>>>( d_base, 2 );

    // Evaluate using proxy kernel.
    PrintClass<<<1, 1>>>( d_base );
    hipDeviceSynchronize();

    // Delete Base object on GPU.
    delete_base<<<1, 1>>>( d_base );
}