project(EngineDependencies)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(spdlog)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(glad INTERFACE "${CMAKE_CURRENT_LIST_DIR}/glad/include")

target_link_libraries(${PROJECT_NAME} INTERFACE
	glad
	glfw
	glm
	spdlog
)