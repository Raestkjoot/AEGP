# Basic project options
cmake_minimum_required(VERSION "3.19.2")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Game)

# Build Engine static library
add_subdirectory(Engine)

# Build executable
file(GLOB_RECURSE GameSource "Game/Source/*.cpp" "Game/Source/*.h")
add_executable(Game "Game/Source/Main.cpp" ${GameSource})
target_link_libraries(Game Engine)