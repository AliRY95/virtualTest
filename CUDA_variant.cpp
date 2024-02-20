#include <iostream>
#include <cuda/std/variant>
#include <variant>
#include <cuda.h>


struct A{};
struct B{};
struct Visitor {
  __device__
  void operator()(const A&) { printf("It's an A!\n"); }
  __device__
  void operator()(const B&) { printf("It's a  B!\n"); }
};

__global__
void visitVariant() {
  cuda::std::variant<A, B> var{A{}};
  cuda::std::visit(Visitor{}, var);
}

int main() {
  visitVariant<<<1, 1>>>();
  cudaDeviceSynchronize();
  return 0;
}