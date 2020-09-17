#ifndef TBB_MATRIX_HXX
#define TBB_MATRIX_HXX


#include <cstdlib>
#include <memory>
#include <vector>
#include <sstream>
#include <execution>
#include "vec_matrix.hxx"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

template<typename T>
class TbbMatrix : public VecMatrix<T>{
  
public:
  
  TbbMatrix<T>(size_t m, size_t n):
    VecMatrix<T>(m, n){
  }
  virtual ~TbbMatrix<T>(){
  };
  
  std::unique_ptr<Matrix> operator*(const Matrix & other) const override{

    const TbbMatrix<T>& m_other = dynamic_cast<const TbbMatrix<T>&>(other);
    auto m_product = std::make_unique<TbbMatrix<T>>(this->m_,m_other.n_);

    tbb::parallel_for( tbb::blocked_range<int>(0,m_other.n_),
                    [&](tbb::blocked_range<int> r){
        for (int id_i=r.begin(); id_i<r.end(); ++id_i){                  
          for(size_t id_j=0;id_j<m_other.n_;id_j++){
            for(int id_k=0;id_k<this->n_;id_k++){
              //  cij=Sum(aik*bkj)
              m_product->data_[id_i*m_product->n_+id_j]+=this->data_[id_i*this->n_+id_k]*m_other.data_[id_k*m_other.n_+id_j];
            }
          }
        } 

    });
    

    return m_product;
  }
};


#endif
