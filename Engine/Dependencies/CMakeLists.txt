project(EngineDependencies)

add_subdirectory(spdlog)
add_subdirectory(glm)
add_subdirectory(SDL)

add_library(${PROJECT_NAME} INTERFACE)

include_directories(${PROJECT_NAME} INTERFACE "SDL/include")
target_link_directories(${PROJECT_NAME} INTERFACE "$SDL/lib/x64")
target_link_libraries(${PROJECT_NAME} INTERFACE SDL2 SDL2main)

target_link_libraries(${PROJECT_NAME} INTERFACE
	spdlog
	glm
	SDL2
	SDL2main
)