#ifndef DGEMM_KERNEL_HXX
#define DGEMM_KERNEL_HXX

#include "../../core/kernel.hxx"
#include "../../types/matrix.hxx"


// Dgemm standard Kernel
class DgemmKernel: public Kernel<std::pair<Matrix*,Matrix*>,Matrix>{
public:
  
  // Constructor
  DgemmKernel() = default;

  std::unique_ptr<Matrix> execute(const std::pair<Matrix*,Matrix*> & input){
    return((*input.first)*(*input.second));
  }
  

};

#endif
