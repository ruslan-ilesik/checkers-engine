cmake_minimum_required(VERSION 3.23)
project(checkers_engine)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(checkers_engine
        src/board.cpp
        src/board.hpp
        src/move.cpp
        src/move.hpp
        main.cpp)
