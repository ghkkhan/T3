cmake_minimum_required(VERSION 2.8)

# ALL OF THE SPECIFIED NAMES IN THIS CMAKE ARE REQUIRED.
# Set the project name variable to assignment3.
# THIS IS REQUIRED
project(TTT)

# Add your CMAKE_C_FLAGS AND CMAKE_CXX_FLAGS here
# Make SURE to use -std=c11 and -std=c++11 where relevant.
# The options specified below are required, but additional options
#  may be used.
set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror")
set(CMAKE_CXX_FLAGS "-std=c++11" )

# Add our include directory to CMake's search paths.
# THIS IS REQUIRED
include_directories(includes)

add_library(Board SHARED src/Board.cpp)
add_library(AI SHARED src/AI.cpp)
add_executable(Main src/main.cpp)

# link the Board library we compiled against the Main executable.
target_link_libraries(Main Board AI)