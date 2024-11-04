project(EngineDependencies)

add_subdirectory(EnTT)
add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(imgui)
add_subdirectory(json)
add_subdirectory(spdlog)
add_subdirectory(stb)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE
	glad
	glfw
	glm
	imgui
	nlohmann_json::nlohmann_json
	spdlog
	stb
	EnTT::EnTT
)