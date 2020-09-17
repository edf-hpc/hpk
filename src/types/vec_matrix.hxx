#ifndef VEC_MATRIX_HXX
#define VEC_MATRIX_HXX

#include <iostream>
#include <vector>
#include "matrix.hxx"

// This class defines methods common to matrix classes
// that use a stl vector to store values.
template<typename T>
class VecMatrix : public Matrix{
  
protected:
  size_t m_;
  size_t n_;
  std::vector<T> data_;

public:

  VecMatrix<T>(size_t m, size_t n):
    m_(m),n_(n),data_(m*n,T()){
  }

  VecMatrix<T>(const VecMatrix<T>& other) = default;

  virtual ~VecMatrix(){
  };

  virtual int fill(){
    for(auto it_m=0; it_m!=data_.size(); it_m++){
      data_[it_m] += it_m;
    }
    if (data_.empty())
    {
      return 1;
    }
    return 0;
  }
  
  virtual int fill(std::vector<T> content, size_t m, size_t n){
    data_= content;
    return 0;
  };
  
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
  
};
  

#endif
