#include <hip/hip_runtime.h>
#include <iostream>


class Base
{
public:
    __host__ __device__ Base() {}
    __host__ __device__ virtual ~Base() {}
    __host__ __device__ virtual void increaseInt()
    { printf( "increaseInt is not implemented for Base class!\n" ); }
    __host__ __device__ virtual void printInt() const = 0;
};

class Derived : public Base
{
private:
    int m_int;
public:
    __host__ __device__ Derived( int myInt ) : m_int( myInt ) {}
    __host__ __device__ ~Derived() {}
    __host__ __device__ void increaseInt() 
    { m_int++; }
    __host__ __device__ void printInt() const 
    { printf( "my value is %d.\n", m_int ); }
};





// -----------------------------------------------------------------------------
// KERNELS
__global__ void create_base( Base** base, int myInt )
{
    printf( "printf on GPU!\n" );
    if ( threadIdx.x == 0 && blockIdx.x == 0 )
        (*base) = new Derived( myInt );
}

__global__ void increase_and_print( Base** base )
{
    if ( threadIdx.x == 0 && blockIdx.x == 0 )
    {
        (*base)->increaseInt();
        (*base)->printInt();
    }
}

__global__ void delete_base( Base** base )
{
    delete *base;
}




// -----------------------------------------------------------------------------
// Main
int main()
{   
    // HOST CODE
    printf( "Host started!\n" );
    // Create Base
    Base* h_base;
    h_base = new Derived( 10 );
    // Virtual call
    h_base->increaseInt();
    h_base->printInt();
    // Free memory
    delete h_base;
    printf( "Host finished!\n" );
    
    
    // DEVICE CODE
    printf( "Device started!\n" );
    // Create Base
    Base** d_base;
    hipMalloc( (void**) &d_base, sizeof( Base** ) );
    create_base<<<1, 1>>>( d_base, 20 );
    // Virtual call
    increase_and_print<<<1, 1>>>( d_base );    
    // Free memory
    delete_base<<<1, 1>>>( d_base );
    hipDeviceSynchronize();
    printf( "Device finished!\n" );
}
