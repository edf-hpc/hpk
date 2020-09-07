#ifndef TBB_MATRIX_HXX
#define TBB_MATRIX_HXX


#include <cstdlib>
#include <memory>
#include <vector>
#include <sstream>
#include <execution>
#include "matrix.hxx"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

template<typename T>
class TbbMatrix : public Matrix{
  
public:
  
  TbbMatrix<T>(size_t m, size_t n):
    m_(m),n_(n),data_(m*n,T()){
  }
  virtual ~TbbMatrix<T>(){
  };
  

  int fill() override{
#pragma omp for
    for(auto it_m=0; it_m!=data_.size(); it_m++){
      //*it_m = data_.at(it_m) +1 ;
      data_[it_m] += it_m;
  
    }

    return 0;
  }




  std::unique_ptr<Matrix> operator*(const Matrix & other) const override{

    const TbbMatrix<T>& m_other = dynamic_cast<const TbbMatrix<T>&>(other);
    auto m_product = std::make_unique<TbbMatrix<T>>(this->m_,m_other.n_);

    tbb::parallel_for( tbb::blocked_range<int>(0,m_other.n_),
                    [&](tbb::blocked_range<int> r){
        for (int id_i=r.begin(); id_i<r.end(); ++id_i){                  
          for(size_t id_j=0;id_j<m_other.n_;id_j++){
            for(int id_k=0;id_k<n_;id_k++){
              //  cij=Sum(aik*bkj)
              m_product->data_[id_i*m_product->n_+id_j]+=data_[id_i*n_+id_k]*m_other.data_[id_k*m_other.n_+id_j];
            }
          }
        } 

    });
    

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
