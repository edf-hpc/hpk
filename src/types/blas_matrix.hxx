#ifndef BLAS_MATRIX_HXX
#define BLAS_MATRIX_HXX

#include <cblas.h>
#include <cstdlib>
#include <memory>
#include <vector>
#include <sstream>
#include "vec_matrix.hxx"


template<typename T>
class BlasMatrix : public VecMatrix<T>{
  
public:
  
  BlasMatrix<T>(size_t m, size_t n):
    VecMatrix<T>(m, n){
  }
  virtual ~BlasMatrix<T>(){
  };
  
  std::unique_ptr<Matrix> operator*(const Matrix & other) const override{
    
    const BlasMatrix<T>& m_other = dynamic_cast<const BlasMatrix<T>&>(other);
    auto m_product = std::make_unique<BlasMatrix<T>>(this->m_, m_other.n_);
    
    // C = alpha * A * B + beta * C
    cblas_dgemm( CblasRowMajor,  CblasNoTrans, CblasNoTrans,
		 this->m_, m_other.n_, this->n_,
		 1, &(this->data_[0]), this->n_, // alpha, A, lda
		 &m_other.data_[0], m_other.n_,              // B, ldb
		 0, &m_product->data_[0], m_other.n_); // beta, C, ldc
    
    return m_product;
  }

};


#endif

