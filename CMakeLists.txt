cmake_minimum_required(VERSION 3.5)
project(NineColumGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/Point.cpp src/Point.h src/GameBoard.cpp src/GameBoard.h src/GameStatus.h)
add_executable(NineColumGame ${SOURCE_FILES})