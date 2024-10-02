project(Engine)

add_subdirectory(Dependencies)
add_subdirectory(Source)


# Copy project data to output path
file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})