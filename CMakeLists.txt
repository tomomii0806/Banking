cmake_minimum_required(VERSION 3.14)
project(HW6_Banking)

set(CMAKE_CXX_STANDARD 14)

add_executable(HW6_Banking main.cpp BSTree.h Account.cpp Account.h Bank.h Bank.cpp BSTree.cpp)