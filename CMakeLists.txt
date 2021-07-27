cmake_minimum_required(VERSION 3.18)

project(linux)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -DCMAKE_BUILD_TYPE=Debug" )

set(CMAKE_CXX_STANDARD 11)


#------------------Atmoics and threading------------------

add_executable(linux AtomicsAndThreading/threadPool/thread_pool.cpp)