cmake_minimum_required (VERSION 3.7)
project (HPK VERSION 0.1.0 LANGUAGES CXX)

# Versionning
set (HPK_VERSION_MAJOR 1)
set (HPK_VERSION_MINOR 0)

# Executable
add_executable(hpk core/hpk.cxx)
add_executable(double_dgemm ../examples/double_dgemm.cxx)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

target_include_directories(hpk
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
	)

target_include_directories(double_dgemm
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
	)
      
target_compile_features(hpk PRIVATE cxx_std_17)
target_compile_features(double_dgemm PRIVATE cxx_std_17)

# Blas support
find_package(BLAS REQUIRED)
if(BLAS_FOUND)
    message("OpenBLAS found.")
    target_link_libraries(hpk ${BLAS_LIBRARIES})
    target_link_libraries(double_dgemm ${BLAS_LIBRARIES})
endif(BLAS_FOUND)

#message("TBB found.")
target_link_libraries(hpk -L${TBB_LIB_DIR} -ltbb)
target_link_libraries(double_dgemm -L${TBB_LIB_DIR} -ltbb)

# Install
install (TARGETS hpk DESTINATION bin)
install (TARGETS double_dgemm DESTINATION bin)
