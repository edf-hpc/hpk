cmake_minimum_required (VERSION 3.7)
project (HPK VERSION 0.1.0 LANGUAGES CXX)

# Versionning
set (HPK_VERSION_MAJOR 1)
set (HPK_VERSION_MINOR 0)


# Executable
add_executable(hpk core/hpk.cxx)
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/)

target_include_directories(hpk
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
  )
target_compile_features(hpk PRIVATE cxx_std_17)


# Blas support
find_package(BLAS REQUIRED)
if(BLAS_FOUND)
    message("OpenBLAS found.")
    target_link_libraries(hpk ${BLAS_LIBRARIES})
endif(BLAS_FOUND)



# Install
install (TARGETS hpk DESTINATION bin)
