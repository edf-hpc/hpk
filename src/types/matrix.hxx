#ifndef MATRIX_HXX
#define MATRIX_HXX

#include<iostream>


// Abstract Matrix class with standard operators
// Operator implementations in subclass 
class Matrix{

public:

  
  //  virtual Matrix<T>(size_t m, size_t n)=0;
  virtual ~Matrix(){
  };

  virtual int fill()=0;
  
  virtual std::unique_ptr<Matrix> operator*(const Matrix & other) const=0;

  virtual std::string to_string() const=0;
  
  friend std::ostream& operator<<(std::ostream& stream, const Matrix& matrix){
    return stream<<matrix.to_string();
  }
};
  

#endif
