file(GLOB_RECURSE EngineSource "*.cpp" "*.h")

add_library(${PROJECT_NAME} ${EngineSource})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC EngineDependencies)