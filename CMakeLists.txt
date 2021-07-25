cmake_minimum_required(VERSION 3.18)

project(linux)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -DCMAKE_BUILD_TYPE=Debug" )

set(CMAKE_CXX_STANDARD 11)


#------------------Atmoics and threading------------------
#AtomicsAndThreading/thread/createThread.cpp

#AtomicsAndThreading/conditionVariable/notify_one.cpp
#AtomicsAndThreading/lock/lock_guard.cpp
#AtomicsAndThreading/mutex/call_one.cpp
add_executable(linux AtomicsAndThreading/future/promise.cpp)