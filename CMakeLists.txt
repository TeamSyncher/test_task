cmake_minimum_required(VERSION 3.0)

project (pc_club_logger)

set(CMAKE_CXX_STANDART 14)

#set(CMAKE_CPP_COMPILER "C:\MinGW\bin\c++")

include_directories(headers)

file(GLOB CPPS "*.cpp")

add_executable(${PROJECT_NAME} ${CPPS})