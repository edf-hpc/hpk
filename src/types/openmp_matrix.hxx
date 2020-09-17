#ifndef OPENMP_MATRIX_HXX
#define OPENMP_MATRIX_HXX


#include <cstdlib>
#include <memory>
#include <omp.h>
#include <vector>
#include <sstream>
#include "vec_matrix.hxx"

template<typename T>
class OpenmpMatrix : public VecMatrix<T>{
  
public:
  
  OpenmpMatrix<T>(size_t m, size_t n):
    VecMatrix<T>(m, n){
  }
  virtual ~OpenmpMatrix<T>(){
  };
  
  std::unique_ptr<Matrix> operator*(const Matrix & other) const override{

    const OpenmpMatrix<T>& m_other = dynamic_cast<const OpenmpMatrix<T>&>(other);
    auto m_product = std::make_unique<OpenmpMatrix<T>>(this->m_,m_other.n_);

#pragma omp for
    for(int id_i=0;id_i<this->m_;id_i++){
      for(int id_j=0;id_j<m_other.n_;id_j++){
	for(int id_k=0;id_k<this->n_;id_k++){
	  //  cij=Sum(aik*bkj)
	  m_product->data_[id_i*m_product->n_+id_j]+=this->data_[id_i*this->n_+id_k]*m_other.data_[id_k*m_other.n_+id_j];
	}
      }
    }
    
    return m_product;
  }
};


#endif
