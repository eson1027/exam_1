cmake_minimum_required(VERSION 3.8)

# Define the project name of these source code
project (adder-rdyvld)

# Define the C++ standard -std=c++17
# This is required to match the systemc installed with Ubuntu
set (CMAKE_CXX_STANDARD 17)

# Add optimization & warning flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

# Define the executable name and its source code
file(GLOB SRC "*.cpp")
add_executable(adder-rdyvld ${SRC})

# Define the used libraries of the executable, Equal to -l flags of g++
target_link_libraries(adder-rdyvld systemc)

