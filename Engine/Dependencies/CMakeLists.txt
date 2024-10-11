project(EngineDependencies)

add_subdirectory(EnTT)
add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(spdlog)
add_subdirectory(stb)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE
	glad
	glfw
	glm
	spdlog
	stb
	EnTT::EnTT
)