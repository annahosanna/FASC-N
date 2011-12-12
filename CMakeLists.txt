cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(FASC-N)

include (CTest)

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FASC-N_BINARY_DIR}/bin)
endif()

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)
