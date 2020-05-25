#ifndef BLAS_MATRIX_HXX
#define BLAS_MATRIX_HXX

#include <cblas.h>
#include <cstdlib>
#include <memory>
#include <vector>
#include <sstream>
#include "matrix.hxx"

template<typename T>
class BlasMatrix : public Matrix{
  
public:
  
  BlasMatrix<T>(size_t m, size_t n):
    m_(m),n_(n),data_(m*n,T()){
  }
  virtual ~BlasMatrix<T>(){
  };
  
  int random_fill(std::any min, std::any max) override{
    T cmin = std::any_cast<T>(min);
    T cmax = std::any_cast<T>(max);
#pragma omp for
    for(auto it_m=data_.begin(); it_m!=data_.end(); it_m++){
      *it_m = cmin + (static_cast<T>(std::rand()) / RAND_MAX)*(cmax-cmin);
    }

    return 0;
  }
  
  std::unique_ptr<Matrix> operator*(const Matrix & other) const override{
    
    const BlasMatrix<T>& m_other = dynamic_cast<const BlasMatrix<T>&>(other);
    auto m_product = std::make_unique<BlasMatrix<T>>(this->m_, m_other.n_);
    
    // C = alpha * A * B + beta * C
    cblas_dgemm( CblasRowMajor,  CblasNoTrans, CblasNoTrans,
		 m_, m_other.n_, n_,
		 1, &(this->data_[0]), n_, // alpha, A, lda
		 &m_other.data_[0], m_other.n_,              // B, ldb
		 0, &m_product->data_[0], m_other.n_); // beta, C, ldc
    
    return m_product;
  }
  std::string to_string() const override{
    // Print with Python formatting
    std::ostringstream output;
    output<<std::endl<<"[";
    int id=0;
    for (auto &val: data_){
      if (id==0)
	output<<"["<<val;
      else if (id%n_==0)
	output<<"],["<<val;
      else
	output<<","<<val;
      id++;
    }
    output<<"]]"<<std::endl;
    return output.str();
  }

private:
  size_t m_;
  size_t n_;
  std::vector<T> data_;
};


#endif

