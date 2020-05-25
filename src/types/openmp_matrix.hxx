#ifndef OPENMP_MATRIX_HXX
#define OPENMP_MATRIX_HXX


#include <cstdlib>
#include <memory>
#include <omp.h>
#include <vector>
#include <sstream>
#include "matrix.hxx"

template<typename T>
class OpenmpMatrix : public Matrix{
  
public:
  
  OpenmpMatrix<T>(size_t m, size_t n):
    m_(m),n_(n),data_(m*n,T()){
  }
  virtual ~OpenmpMatrix<T>(){
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

    const OpenmpMatrix<T>& m_other = dynamic_cast<const OpenmpMatrix<T>&>(other);
    auto m_product = std::make_unique<OpenmpMatrix<T>>(this->m_,m_other.n_);

#pragma omp for
    for(int id_i=0;id_i<m_;id_i++){
      for(int id_j=0;id_j<m_other.n_;id_j++){
	for(int id_k=0;id_k<n_;id_k++){
	  //  cij=Sum(aik*bkj)
	  m_product->data_[id_i*m_product->n_+id_j]+=data_[id_i*n_+id_k]*m_other.data_[id_k*m_other.n_+id_j];
	}
      }
    }
    
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
