project(Engine)

add_subdirectory(Dependencies)

file(GLOB_RECURSE EngineSource "Source/*.cpp" "Source/*.h")
add_library(${PROJECT_NAME} STATIC ${EngineSource})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_link_libraries(${PROJECT_NAME} PUBLIC EngineDependencies)

# Copy project data to output path
file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})