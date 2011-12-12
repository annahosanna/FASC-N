cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(FASC-N)

include (CTest)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
