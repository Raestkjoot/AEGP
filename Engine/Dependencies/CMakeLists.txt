project(EngineDependencies)

add_subdirectory(spdlog)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE
	spdlog
)