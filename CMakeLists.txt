cmake_minimum_required(VERSION 3.12)
project(Szakdolgozat)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
add_subdirectory(src)
add_subdirectory(test)