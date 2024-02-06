cmake_minimum_required(VERSION 3.0)

project (test1)

set(CMAKE_CXX_STANDART 14)

#set(CMAKE_CPP_COMPILER "C:\MinGW\bin\c++")

file(GLOB CPPS "*.cpp")

add_executable(${PROJECT_NAME} ${CPPS})