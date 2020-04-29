cmake_minimum_required(VERSION 3.10.2)

# set(CMAKE_CXX_STANDARD 17)
project(dihedral)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -Wall")

# Find all executables
file(GLOB project_SRCS src/*.cpp)

# Add project executable
add_executable(dihedral ${project_SRCS})
