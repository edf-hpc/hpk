#ifndef PSTL_MATRIX_HXX
#define PSTL_MATRIX_HXX


#include <cstdlib>
#include <memory>
#include <vector>
#include <functional>
#include <sstream>
#include <execution>
#include <algorithm>
#include <numeric>
#include "vec_matrix.hxx"


template<typename T>
class PstlMatrix : public VecMatrix<T>{
  
public:
  
  PstlMatrix<T>(size_t m, size_t n):
    VecMatrix<T>(m, n){
  }

  virtual ~PstlMatrix<T>(){
  };
      
  std::unique_ptr<Matrix> operator*(const Matrix & other) const override{

    const PstlMatrix<T>& m_other = dynamic_cast<const PstlMatrix<T>&>(other);
    auto m_product = std::make_unique<PstlMatrix<T>>(this->m_,m_other.n_);

      // Copy Left Matrix
      PstlMatrix<T> m_other_cpy = m_other;

      // Transpose 
      for(int ii=0;ii<this->n_;ii++){
        for(int jj=0;jj<this->m_;jj++){
          m_other_cpy.data_[jj*(this->n_)+ii] = m_other.data_[ii*(this->m_)+jj];
        }
      }

    auto LM_line_start = this->data_.begin();
    auto LM_line_end = this->data_.begin();
    
    std::advance(LM_line_end,this->n_);

    auto RM_line_start = m_other_cpy.data_.begin();
    
    for(int id_i=0;id_i<this->m_;id_i++){
      for(int id_j=0;id_j<m_other_cpy.n_;id_j++){
        m_product->data_[id_j*m_product->n_+id_i]= std::transform_reduce( std::execution::par, LM_line_start, LM_line_end, RM_line_start, 0.0);
        
        // Update Itérate Left matrice
        std::advance(LM_line_start,this->n_);
        std::advance(LM_line_end,this->n_);

      }
      // // ré-Itérate Right matrice
      LM_line_start = this->data_.begin();
      LM_line_end = this->data_.begin();
    
      std::advance(LM_line_end,this->n_);

      // Itérate Right matrice 
      std::advance(RM_line_start,this->n_);
    } 
    
    return m_product;
  }

};


#endif
