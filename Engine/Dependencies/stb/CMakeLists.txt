add_library(stb INTERFACE "include/stb_image.h")
target_include_directories(stb INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")