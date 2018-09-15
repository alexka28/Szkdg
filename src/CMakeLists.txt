set(core_SRCS Main.cpp CreateInsertQuery.cpp CreateInsertQuery.h DecrementalGraph.cpp DecrementalGraph.h DFS.cpp DFS.h GraphGen.cpp GraphGen.h IncrementalAlgorithm.cpp IncrementalAlgorithm.h Test.cpp Test.h TraditionalAlgorithm.cpp TraditionalAlgorithm.h UniFind.cpp UniFind.h  ETT.cpp ETT.h CreateDeleteQuery.h CreateDeleteQuery.cpp TestETT.cpp TestETT.h ETTSetter.cpp ETTSetter.h ETTUpdater.cpp ETTUpdater.h ETTQueries.cpp ETTQueries.h)
add_library(core ${core_SRCS})
add_executable(exe main.cpp)
target_link_libraries(exe core)