#include <iostream>
#include <string>
#include "../types/blas_matrix.hxx"
#include "../types/openmp_matrix.hxx"
#include "../kernels/dgemm/dgemm_kernel.hxx"
#include "hpk_utils.hxx"


std::unique_ptr<Matrix> run(std::pair<Matrix*,Matrix*> input){
  // Run dgemm kernel and return result

  auto dgemm_kernel = std::make_unique<DgemmKernel>();

  return(dgemm_kernel->execute(input));

}


int main(void){
  std::cout<<"HPK project:"<<hpk_code<<std::endl;

  // OpenMP matrix multiplication
  std::unique_ptr<Matrix> ma = std::make_unique<OpenmpMatrix<double>>(2,3);
  std::unique_ptr<Matrix> mb = std::make_unique<OpenmpMatrix<double>>(3,2);
  ma->random_fill(3.0,4.0);
  mb->random_fill(3.0,4.0);

  std::cout<<std::endl<<"A-openmp:"<<*ma;
  std::cout<<"B-openmp:"<<*mb;
  std::unique_ptr<Matrix> mc = (*ma)*(*mb);
  std::cout<<"C-openmp:"<<*mc;

  // Blas matrix multiplication
  std::unique_ptr<Matrix> ma_blas = std::make_unique<BlasMatrix<double>>(2,3);
  std::unique_ptr<Matrix> mb_blas = std::make_unique<BlasMatrix<double>>(3,2);
  ma_blas->random_fill(3.0,4.0);
  mb_blas->random_fill(3.0,4.0);
  std::cout<<std::endl<<"A-Blas:"<<*ma_blas;
  std::cout<<"B-Blas:"<<*mb_blas;

  std::unique_ptr<Matrix> mc_blas = (*ma_blas)*(*mb_blas);
  std::cout<<"C-Blas:"<<*mc_blas;

  // Dgemm Kernel with OpenMP matrices
  auto mc_kernel_openmp = run(std::pair<Matrix*,Matrix*>(ma.get(), mb.get()));
  std::cout<<std::endl<<"C-Dgemm-OpenMP:"<<*mc_kernel_openmp;

  // Dgemm Kernel with Blas matrices
  auto mc_kernel_blas = run(std::pair<Matrix*,Matrix*>(ma_blas.get(), mb_blas.get()));
  std::cout<<std::endl<<"C-Dgemm-Blas:"<<*mc_kernel_blas;

  
}
