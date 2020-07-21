#include <iostream>
#include <string>
#include "../src//types/blas_matrix.hxx"
#include "../src/types/openmp_matrix.hxx"
#include "../src/kernels/dgemm/dgemm_kernel.hxx"

template<typename MatrixType>
std::unique_ptr<Matrix> double_dgemm(){
  // Compute ma*mb*mc

  std::unique_ptr<Matrix> ma = std::make_unique<MatrixType>(2,3);
  std::unique_ptr<Matrix> mb = std::make_unique<MatrixType>(3,2);  
  std::unique_ptr<Matrix> mc = std::make_unique<MatrixType>(3,2);

  ma->random_fill(0.0,1.0);
  mb->random_fill(0.0,1.0);
  mc->random_fill(0.0,1.0);

  DgemmKernel dgemm_kernel;
  return(dgemm_kernel.execute(std::pair(dgemm_kernel.execute(std::pair(ma.get(),mb.get())).get(),
					mc.get())));
}

int main(void){
  std::cout<<std::endl<<"2xDgemm-OpenMP result:"<<*double_dgemm<OpenmpMatrix<double>>();
  std::cout<<std::endl<<"2xDgemm-Blas result:"<<*double_dgemm<BlasMatrix<double>>();
}
