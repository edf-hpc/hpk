HPK (High Performance Kernels) project goal is to provide a way to benchmark multiple implementations
of standard HPC algorithms. Algorithms are built with compute kernels describing abstract high level
algorithm workflows. Lower level optimisations and parallelisations are done within classes holding
data.

For example the *Dgemm kernel* only describes that a multiplication between two matrices of abstract
type *Matrix* should be computed. The way the multiplication is done is implemented in Matrix subclasses
like *OpenmpMatrix* or *BlasMatrix*.

This software uses c++17 features and was tested with gcc 8.2 and cmake 3.7.