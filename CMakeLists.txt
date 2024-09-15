# Basic project options
cmake_minimum_required(VERSION "3.19.2")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Hello)

# Build Engine static library
add_subdirectory(Engine)

# Build executable
add_executable(Hello "Game/Source/main.cpp")
target_link_libraries(Hello Engine)