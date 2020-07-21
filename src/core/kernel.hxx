#ifndef KERNEL_HXX
#define KERNEL_HXX

#include <string>
#include <vector>

template <typename InputType,typename OutputType>
class Kernel {
public:
  Kernel(){
  }

  virtual std::unique_ptr<OutputType> execute(const InputType& input) = 0;

  std::vector<std::string> list_impl(){
    return(std::vector<std::string>({""}));
  }
  

};



#endif
