cmake_minimum_required(VERSION 3.16)
project(Automata_Example
  VERSION 0.0.1
  LANGUAGES CXX
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g")  # can add / remove flags here

add_subdirectory(source)
# other subdirectories here if necessary

set(Catch2_DIR "~/vcpkg/installed/x64-linux/share/catch2")
find_package(Catch2 3 REQUIRED) # add 'PATHS /path/to/local/install' if required.  
add_subdirectory(test)
