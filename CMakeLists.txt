cmake_minimum_required(VERSION 3.10)
project(untitled1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(untitled1 Main.cpp CreateInsertQuery.cpp CreateInsertQuery.h DecrementalGraph.cpp DecrementalGraph.h DFS.cpp DFS.h GraphGen.cpp GraphGen.h IncrementalAlgorithm.cpp IncrementalAlgorithm.h Test.cpp Test.h TraditionalAlgorithm.cpp TraditionalAlgorithm.h UniFind.cpp UniFind.h  ETT.cpp ETT.h CreateDeleteQuery.h CreateDeleteQuery.cpp TestETT.cpp TestETT.h)