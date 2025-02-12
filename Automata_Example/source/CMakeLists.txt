add_executable(Automata automaton.cpp)
target_include_directories(Automata PUBLIC ${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../include)