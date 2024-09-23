include_directories(include)
add_library(glad STATIC "include/glad/glad.h;src/glad.c")
target_include_directories(glad INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")